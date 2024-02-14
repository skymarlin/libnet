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

#include <functional>
#include <unordered_map>

#include <skymarlin/network/Packet.hpp>

namespace skymarlin::network
{
class PacketResolver final
{
public:
    static void Register(const std::vector<std::pair<PacketProtocol, PacketFactory>>& factories);
    static std::shared_ptr<Packet> Resolve(PacketProtocol type);

private:
    inline static std::unordered_map<PacketProtocol, PacketFactory> factory_map_ {};
};


inline void PacketResolver::Register(const std::vector<std::pair<PacketProtocol, PacketFactory>>& factories)
{
    for (const auto& [type, factory] : factories) {
        factory_map_[type] = factory;
    }
}

inline std::shared_ptr<Packet> PacketResolver::Resolve(const PacketProtocol type)
{
    if (!factory_map_.contains(type)) {
        return nullptr;
    }
    return factory_map_[type]();
}
}
