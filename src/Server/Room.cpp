#include "pch.h"
#include "Room.h"

std::shared_ptr<Room> Room::Create(const asio::executor& executor)
{
    return std::shared_ptr<Room>(new Room(executor));
}

asio::awaitable<void> Room::AddClientConnectionAsync(
    std::shared_ptr<ClientConnection> const& clientConnection)
{
    auto strongThis{ shared_from_this() };
    co_await asio::post(m_strand, asio::use_awaitable);

    for (const auto& client : m_clientConnections)
    {
        co_await client->SendMessageAsync("A new client has joined!\n");
    }

    m_clientConnections.push_back(clientConnection);
    co_await clientConnection->SendMessageAsync("Welcome!\n");
}

Room::Room(const asio::executor& executor) : m_strand{ asio::make_strand(executor) }
{ }
