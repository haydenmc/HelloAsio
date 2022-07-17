#include "ClientConnection.h"

std::shared_ptr<ClientConnection> ClientConnection::Create(const asio::executor& executor,
    asio::ip::tcp::socket&& socket)
{
    return std::shared_ptr<ClientConnection>(new ClientConnection(executor, std::move(socket)));
}

asio::awaitable<void> ClientConnection::SendMessageAsync(std::string_view message)
{
    auto strongThis{ shared_from_this() };
    co_await asio::post(m_strand, asio::use_awaitable);
    spdlog::info("Sending message to client {}:{}",
        strongThis->m_socket.remote_endpoint().address().to_string(),
        strongThis->m_socket.remote_endpoint().port());
    co_await asio::async_write(strongThis->m_socket, asio::buffer(message.data(), message.size()),
        asio::use_awaitable);
}

ClientConnection::ClientConnection(const asio::executor& executor, asio::ip::tcp::socket&& socket) :
    m_strand{ executor }, m_socket{ std::move(socket) }
{ }
