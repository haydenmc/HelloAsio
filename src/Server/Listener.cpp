#include "pch.h"
#include "Listener.h"

std::shared_ptr<Listener> Listener::Create(const asio::executor& executor,
    const std::shared_ptr<Room>& room, const uint16_t portNumber)
{
    return std::shared_ptr<Listener>(new Listener(executor, room, portNumber));
}

asio::awaitable<void> Listener::ListenAsync()
{
    auto strongThis{ shared_from_this() };
    asio::ip::tcp::acceptor acceptor{ co_await asio::this_coro::executor,
        asio::ip::tcp::endpoint{ asio::ip::tcp::v4(), strongThis->m_portNumber} };
    spdlog::info("Listening for connections on port {}", strongThis->m_portNumber);
    while (true)
    {
        asio::ip::tcp::socket socket{ co_await acceptor.async_accept(asio::use_awaitable) };
        spdlog::info("Accepted connection from {}:{}",
            socket.remote_endpoint().address().to_string(),
            socket.remote_endpoint().port());
        auto clientConnection{ ClientConnection::Create(m_strand.get_inner_executor(),
            std::move(socket)) };
        co_await strongThis->m_room->AddClientConnectionAsync(clientConnection);
    }
}

Listener::Listener(const asio::executor& executor,
    const std::shared_ptr<Room>& room, const uint16_t portNumber) :
    m_strand{ executor }, m_room{ room }, m_portNumber{ portNumber }
{ }

