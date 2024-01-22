#pragma once

#include <skymarlin/network/Listener.hpp>
#include <skymarlin/network/Session.hpp>

namespace skymarlin::network {
struct ServerConfig {
    short listen_port;
    Session::SessionCreator session_creator;
};

class Server : boost::noncopyable {
public:
    explicit Server(ServerConfig&& config);

    virtual ~Server() = default;

    void Run();

protected:
    //TODO: Session Manager

private:
    boost::asio::io_context io_context_{};
    Listener listener_;
};
}
