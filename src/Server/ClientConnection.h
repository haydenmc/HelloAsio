#pragma once

class ClientConnection : public std::enable_shared_from_this<ClientConnection>
{
public:
    static std::shared_ptr<ClientConnection> Create(const asio::executor& executor,
        asio::ip::tcp::socket&& socket);

    asio::awaitable<void> SendMessageAsync(std::string_view message);

private:
    ClientConnection(const asio::executor& executor, asio::ip::tcp::socket&& socket);

    asio::strand<asio::executor> const m_strand;
    asio::ip::tcp::socket m_socket;
};