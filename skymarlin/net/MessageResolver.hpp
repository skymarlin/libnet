#pragma once

#include <skymarlin/net/Connection.hpp>
#include <skymarlin/net/Message.hpp>

#include <functional>
#include <unordered_map>

namespace skymarlin::net
{
using MessageFactory = std::function<std::unique_ptr<Message>(std::vector<byte>&&, MessageHeader)>;
using MessageHandler = std::function<void(std::unique_ptr<Message>, std::shared_ptr<Connection>)>;

class MessageResolver final
{
public:
    static void RegisterFactories(std::vector<std::pair<MessageType, MessageFactory>>&& factories);
    static void RegisterHandlers(std::vector<std::pair<MessageType, MessageHandler>>&& handlers);
    static const MessageFactory& ResolveFactory(MessageType type);
    static const MessageHandler& ResolveHandler(MessageType type);

private:
    inline static std::unordered_map<MessageType, MessageFactory> factory_map_ {};
    inline static std::unordered_map<MessageType, MessageHandler> handler_map_ {};

    inline static const MessageFactory empty_factory_ {};
    inline static const MessageHandler empty_handler_ {};
};


inline void MessageResolver::RegisterFactories(std::vector<std::pair<MessageType, MessageFactory>>&& factories)
{
    for (auto& [type, factory] : factories) {
        factory_map_[type] = std::move(factory);
    }
}

inline void MessageResolver::RegisterHandlers(std::vector<std::pair<MessageType, MessageHandler>>&& handlers)
{
    for (auto& [type, handler] : handlers) {
        handler_map_[type] = std::move(handler);
    }
}


inline const MessageFactory& MessageResolver::ResolveFactory(const MessageType type)
{
    if (!factory_map_.contains(type)) {
        return empty_factory_;
    }
    return factory_map_[type];
}

inline const MessageHandler& MessageResolver::ResolveHandler(const MessageType type)
{
    if (!handler_map_.contains(type)) {
        return empty_handler_;
    }
    return handler_map_[type];
}

}
