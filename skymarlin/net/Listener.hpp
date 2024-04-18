#pragma once

#include <boost/asio.hpp>
#include <skymarlin/net/Client.hpp>
#include <skymarlin/net/ClientManager.hpp>
#include <spdlog/spdlog.h>

namespace skymarlin::net {
using boost::asio::ip::tcp;

class Listener final : boost::noncopyable {
public:
    Listener(boost::asio::io_context& io_context, unsigned short port);

    ~Listener() = default;

    void Start();

    void Stop();

private:
    boost::asio::awaitable<void> Listen();

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;

    std::atomic<bool> listening_ {false};
};

inline Listener::Listener(boost::asio::io_context& io_context, const unsigned short port)
    : io_context_(io_context),
    acceptor_(io_context, tcp::endpoint(tcp::v6(), port)) {}

inline void Listener::Start() {
    listening_ = true;
    co_spawn(io_context_, Listen(), boost::asio::detached);
}

inline void Listener::Stop() {
    if (!listening_.exchange(false)) return;

    try {
        acceptor_.close();
    }
    catch (const boost::system::system_error& e) {
        spdlog::error("[Listener] Error closing: {}", e.what());
    }
}

inline boost::asio::awaitable<void> Listener::Listen() {
    spdlog::info("[Listener] Start accepting on {}:{}", acceptor_.local_endpoint().address().to_string(),
        acceptor_.local_endpoint().port());

    while (listening_) {
        tcp::socket socket {io_context_};

        if (const auto [ec] = co_await acceptor_.async_accept(socket, as_tuple(boost::asio::use_awaitable)); ec) {
            spdlog::error("[Listener] Error on accepting: {}", ec.what());
            continue;
        }

        const auto client = ClientManager::CreateClient(io_context_, std::move(socket));
        if (!client) {
            spdlog::error("[Listener] Failed to create a client");
            continue;
        }

        spdlog::debug("[Listener] Accpeted on {}:{}", client->remote_endpoint().address().to_string(),
            client->remote_endpoint().port());
        client->Start();
    }
}
}
