#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <skymarlin/net/Client.hpp>
#include <skymarlin/net/ClientManager.hpp>
#include <skymarlin/util/Log.hpp>

namespace skymarlin::net {
using boost::asio::ip::tcp;

class Listener final : boost::noncopyable {
public:
    Listener(boost::asio::io_context &io_context, boost::asio::ssl::context &ssl_context,
             unsigned short port, ClientFactory &&client_factory);

    ~Listener() = default;

    void Start();

    void Stop();

private:
    boost::asio::awaitable<void> Listen();

    boost::asio::io_context &io_context_;
    boost::asio::ssl::context &ssl_context_;
    tcp::acceptor acceptor_;
    const ClientFactory client_factory_;

    std::atomic<bool> listening_{false};
};

inline Listener::Listener(boost::asio::io_context &io_context, boost::asio::ssl::context &ssl_context,
                          const unsigned short port, ClientFactory &&client_factory)
    : io_context_(io_context),
      ssl_context_(ssl_context),
      acceptor_(io_context, tcp::endpoint(tcp::v6(), port)),
      client_factory_(std::move(client_factory)) {}

inline void Listener::Start() {
    listening_ = true;
    co_spawn(io_context_, Listen(), boost::asio::detached);
}

inline void Listener::Stop() {
    if (!listening_.exchange(false)) return;

    try {
        acceptor_.close();
    } catch (const boost::system::system_error &e) {
        SKYMARLIN_LOG_ERROR("Error closing listener: {}", e.what());
    }
}

inline boost::asio::awaitable<void> Listener::Listen() {
    SKYMARLIN_LOG_INFO("Start listening on {}:{}", acceptor_.local_endpoint().address().to_string(),
                       acceptor_.local_endpoint().port());

    while (listening_) {
        Socket socket(io_context_, ssl_context_);

        if (const auto [ec] = co_await acceptor_.async_accept(socket.lowest_layer(),
                                                              as_tuple(boost::asio::use_awaitable)); ec) {
            SKYMARLIN_LOG_ERROR("Error on accepting: {}", ec.what());
            continue;
        }

        if (const auto [ec] = co_await socket.async_handshake(boost::asio::ssl::stream_base::server,
                                                              as_tuple(boost::asio::use_awaitable)); ec) {
            SKYMARLIN_LOG_ERROR("Error on handshaking: {}", ec.what());
            continue;
        }

        auto client = client_factory_(io_context_, std::move(socket));
        if (!client) {
            SKYMARLIN_LOG_ERROR("Failed to create a client on accept");
            co_return;
        }

        client->Start();
        ClientManager::AddClient(client);
    }
}
}
