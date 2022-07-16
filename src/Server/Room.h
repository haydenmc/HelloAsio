#pragma once
#include "ClientConnection.h"

class Room : public std::enable_shared_from_this<Room>
{
public:
    static std::shared_ptr<Room> Create(const asio::executor& executor);

    asio::awaitable<void> AddClientConnectionAsync(
        std::shared_ptr<ClientConnection> const& clientConnection);

private:
    Room(const asio::executor& executor);

    asio::strand<asio::executor> m_strand;
    std::vector<std::shared_ptr<ClientConnection>> m_clientConnections;
};