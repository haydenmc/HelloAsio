#pragma once
#include "Room.h"

class Listener : public std::enable_shared_from_this<Listener>
{
public:
    static std::shared_ptr<Listener> Create(const asio::executor& executor,
        const std::shared_ptr<Room>& room, const uint16_t portNumber);
    asio::awaitable<void> ListenAsync();

private:
    Listener(const asio::executor& executor, const std::shared_ptr<Room>& room,
        const uint16_t portNumber);

    asio::strand<asio::executor> m_strand;
    std::shared_ptr<Room> const m_room;
    const uint16_t m_portNumber;
};