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

#include <skymarlin/net/Server.hpp>

#include <skymarlin/net/ClientManager.hpp>
#include <skymarlin/utility/Log.hpp>

namespace skymarlin::net
{
Server::Server(ServerConfig&& config, boost::asio::io_context& io_context, ClientFactory&& client_factory)
    : config_(std::move(config)),
    io_context_(io_context),
    listener_(io_context_, ssl_context_, config_.listen_port, std::move(client_factory))
{
    ssl_context_.use_certificate_chain_file(config_.ssl_certificate_chain_file);
    ssl_context_.use_private_key_file(config_.ssl_private_key_file, boost::asio::ssl::context::pem);
}

void Server::Start()
{
    running_ = true;
    listener_.Start();
}

void Server::Stop()
{
    SKYMARLIN_LOG_INFO("Stopping the server...");
    running_ = false;

    listener_.Stop();
    ClientManager::ClearClients();
}
}
