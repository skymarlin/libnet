/*
 * MIT License
 *
 * Copyright (c) 2024 skymarlin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Config.hpp>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include <boost/asio.hpp>
#include <skymarlin/network/Client.hpp>
#include <skymarlin/network/Log.hpp>
#include <skymarlin/network/Server.hpp>
#include <skymarlin/network/Session.hpp>

namespace skymarlin::network::test
{
class TestSession final : public Session
{
public:
    explicit TestSession(boost::asio::io_context& io_context, Socket&& socket)
        : Session(io_context, std::move(socket))
    {
        SKYMARLIN_LOG_INFO("Session created on {}", local_endpoint().address().to_string());
    }

protected:
    void OnOpen() override {}

    void OnClose() override {}
};

class TestServer final : public Server, std::enable_shared_from_this<TestServer>
{
public:
    explicit TestServer(ServerConfig&& config, boost::asio::io_context& io_context)
        : Server(std::move(config), io_context, Session::MakeSessionFactory<TestSession>()) {}

    ~TestServer() override = default;
};

class TestClient final : public Client
{
public:
    explicit TestClient(ClientConfig&& config, boost::asio::io_context& io_context)
        : Client(std::move(config), io_context, Session::MakeSessionFactory<TestSession>()) {}

    ~TestClient() override = default;

    void OnStart() override {}
    void OnStop() override {}
};

TEST(Networking, StartAndStopServer)
{
    boost::asio::io_context io_context {};
    auto io_work_guard = make_work_guard(io_context);

    std::thread server_thread([&io_context] {
        auto make_server_config = []() -> ServerConfig {
            return {
                .listen_port = 55555,
                .ssl_certificate_chain_file = std::format("{}/tests/network/server.test.crt", PROJECT_ROOT),
                .ssl_private_key_file = std::format("{}/tests/network/server.test.key", PROJECT_ROOT)
            };
        };

        auto server = TestServer(make_server_config(), io_context);
        server.Start();
        server.Stop();

        io_context.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    io_work_guard.reset();

    if (server_thread.joinable()) server_thread.join();
}

TEST(Networking, StartAndStopClient)
{
    boost::asio::io_context io_context {};
    auto io_work_guard = make_work_guard(io_context);

    std::thread client_thread([&io_context] {
        auto make_client_config = []() -> ClientConfig {
            return {.remote_adress = "localhost", .remote_port = 55555};
        };

        auto client = TestClient(make_client_config(), io_context);
        client.Start();

        io_context.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    io_work_guard.reset();

    if (client_thread.joinable()) client_thread.join();
}
}
