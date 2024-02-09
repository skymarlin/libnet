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

#pragma once

#include <memory>

#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include <skymarlin/network/Packet.hpp>

namespace skymarlin::network
{
using boost::asio::ip::tcp;
using SessionFactory = std::function<std::shared_ptr<Session>(boost::asio::io_context&, tcp::socket&&)>;
using SessionId = u64;


class Session : public std::enable_shared_from_this<Session>, boost::noncopyable
{
public:
    Session(boost::asio::io_context& io_context, tcp::socket&& socket);
    virtual ~Session();

    void Open();
    void Close(); //TODO: Get error as parameter
    void SendPacket(std::unique_ptr<Packet> packet);

    SessionId id() const { return id_; }
    bool open() const { return !closed_ && !closing_; };
    tcp::endpoint local_endpoint() const { return socket_.local_endpoint(); }
    tcp::endpoint remote_endpoint() const { return socket_.remote_endpoint(); }

protected:
    virtual void OnOpen() = 0;
    virtual void OnClose() = 0;

    boost::asio::io_context& io_context_;

private:
    boost::asio::awaitable<std::unique_ptr<Packet>> ReceivePacket();
    boost::asio::awaitable<PacketHeader> ReadPacketHeader();
    boost::asio::awaitable<std::unique_ptr<Packet>> ReadPacketBody(std::unique_ptr<Packet> packet, PacketLength length);

    tcp::socket socket_;
    byte header_buffer_[PACKET_HEADER_SIZE] {};

    SessionId id_ {0};
    std::atomic<bool> closed_ {true};
    std::atomic<bool> closing_ {false};
};
}
