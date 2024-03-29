#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/core/noncopyable.hpp>
#include <skymarlin/net/Message.hpp>
#include <skymarlin/net/MessageResolver.hpp>
#include <skymarlin/util/Log.hpp>
#include <skymarlin/util/Queue.hpp>

namespace skymarlin::net
{
using boost::asio::ip::tcp;
using Socket = boost::asio::ssl::stream<tcp::socket>;

class Connection final : public std::enable_shared_from_this<Connection>, boost::noncopyable
{
public:
    Connection(boost::asio::io_context& io_context, Socket&& socket);
    ~Connection();

    void Disconnect();
    void StartReceiveMessage();
    void SendMessage(std::shared_ptr<Message> message);

    static boost::asio::awaitable<bool> Connect(Connection& connection, std::string_view host, uint16_t port);

	bool connected() const { return connected_; }
    tcp::endpoint local_endpoint() const { return socket_.lowest_layer().local_endpoint(); }
    tcp::endpoint remote_endpoint() const { return socket_.lowest_layer().remote_endpoint(); }

private:
    boost::asio::awaitable<std::unique_ptr<Message>> ReceiveMessage();
    boost::asio::awaitable<std::optional<MessageHeader>> ReadMessageHeader();
    boost::asio::awaitable<std::optional<std::vector<byte>>> ReadMessageBody(MessageHeader header);
    boost::asio::awaitable<void> SendMessageQueue();
    void HandleMessage(std::unique_ptr<Message> message);

    boost::asio::io_context& io_context_;
    Socket socket_;
    std::atomic<bool> connected_ {true};

    util::ConcurrentQueue<std::shared_ptr<Message>> send_queue_ {};
    std::atomic<bool> send_queue_processing_ {false};
};


inline Connection::Connection(boost::asio::io_context& io_context, Socket&& socket)
    : io_context_(io_context), socket_(std::move(socket)) {}

inline Connection::~Connection()
{
    if (connected_) {
        SKYMARLIN_LOG_WARN("Connection destructing without being disconnected");
    }
}

inline void Connection::StartReceiveMessage()
{
    if (!connected_) return;

    co_spawn(io_context_, [this]()-> boost::asio::awaitable<void> {
        while (connected_) {
            auto message = co_await ReceiveMessage();
            if (!message) continue;

            HandleMessage(std::move(message));
        }
    }, boost::asio::detached);
}

inline void Connection::Disconnect()
{
    if (!connected_.exchange(false)) return;

    co_spawn(io_context_, [this]()-> boost::asio::awaitable<void> {
        auto [ec] = co_await socket_.async_shutdown(as_tuple(boost::asio::use_awaitable));
        if (ec) {
            SKYMARLIN_LOG_ERROR("Error on shutdown socket: {}", ec.what());
        }
    }, boost::asio::detached);
}

inline void Connection::SendMessage(std::shared_ptr<Message> message)
{
    if (!message || !connected_) return;

    send_queue_.Push(std::move(message));

    if (send_queue_processing_.exchange(true)) return;
    co_spawn(io_context_, SendMessageQueue(), boost::asio::detached);
}

inline boost::asio::awaitable<bool> Connection::Connect(Connection& connection, std::string_view host, uint16_t port)
{
    tcp::resolver resolver {connection.io_context_};

    SKYMARLIN_LOG_INFO("Trying to connect to {}:{}", host, port);
    const auto [ec, endpoints] = co_await resolver.async_resolve(host,
        std::format("{}", port), as_tuple(boost::asio::use_awaitable));
    if (ec) {
        SKYMARLIN_LOG_ERROR("Error on resolve: {}", ec.what());
        connection.connected_ = false;
        co_return false;
    }

    if (const auto [ec, endpoint] = co_await async_connect(connection.socket_.lowest_layer(), endpoints,
        as_tuple(boost::asio::use_awaitable)); ec) {
        SKYMARLIN_LOG_ERROR("Error on connect: {}", ec.what());
        connection.connected_ = false;
        co_return false;
    }

    if (const auto [ec] = co_await connection.socket_.async_handshake(boost::asio::ssl::stream_base::client,
        as_tuple(boost::asio::use_awaitable)); ec) {
        SKYMARLIN_LOG_ERROR("Error on handshake: {}", ec.what());
        connection.Disconnect();
        co_return false;
    }

    co_return true;
}

inline boost::asio::awaitable<void> Connection::SendMessageQueue()
{
    while (!send_queue_.empty()) {
        const auto message = send_queue_.Pop();

        /*const MessageHeader& header = message->header();
        //TODO: buffer pooling?
        std::vector<byte> buffer(MessageHeader::HEADER_SIZE + header.size);

        MessageHeader::WriteHeader(std::span(buffer.data(), header.size), header);


        if (!message->Serialize(std::span(buffer.data() + MessageHeader::HEADER_SIZE, header.size))) {
            SKYMARLIN_LOG_ERROR("Failed to serialize packet body");
            Disconnect();
            co_return;
        }*/

        if (const auto [ec, _] = co_await async_write(socket_,
            boost::asio::buffer(message->buffer()), as_tuple(boost::asio::use_awaitable)); ec) {
            SKYMARLIN_LOG_ERROR("Error on sending packet: {}", ec.what());
            Disconnect();
            co_return;
        }
    }

    send_queue_processing_ = false;
}

inline void Connection::HandleMessage(std::unique_ptr<Message> message)
{
    auto& handler = MessageResolver::ResolveHandler(message->header().type);
    if (!handler) return;

    handler(std::move(message), shared_from_this());
}

inline boost::asio::awaitable<std::unique_ptr<Message>> Connection::ReceiveMessage()
{
    const std::optional<MessageHeader> header = co_await ReadMessageHeader();
    if (!header) {
        Disconnect();
        co_return nullptr;
    }

    auto buffer = co_await ReadMessageBody(*header);
    if (!buffer) {
        Disconnect();
        co_return nullptr;
    }

    const auto message_factory = MessageResolver::ResolveFactory(header->type);
    if (!message_factory) {
        Disconnect();
        co_return nullptr;
    }

    auto message = message_factory(std::move(*buffer), *header);

    co_return message;
}

inline boost::asio::awaitable<std::optional<MessageHeader>> Connection::ReadMessageHeader()
{
    std::array<byte, MessageHeader::HEADER_SIZE> buffer {};

    if (const auto [ec, _] = co_await async_read(socket_,
        boost::asio::buffer(buffer), as_tuple(boost::asio::use_awaitable)); ec) {
        SKYMARLIN_LOG_ERROR("Error on receiving packet header: {}", ec.what());
        co_return std::nullopt;
    }

    co_return MessageHeader::ReadHeader(buffer);
}

inline boost::asio::awaitable<std::optional<std::vector<byte>>> Connection::ReadMessageBody(const MessageHeader header)
{
    // Memory buffer = MemoryPool::Allocate(header.size);
    std::vector<byte> buffer(header.size);

    if (const auto [ec, _] = co_await async_read(socket_,
        boost::asio::buffer(buffer), as_tuple(boost::asio::use_awaitable)); ec) {
        SKYMARLIN_LOG_ERROR("Error on receiving packet body: {}", ec.what());
        co_return std::nullopt;
    }

    co_return buffer;
}
}
