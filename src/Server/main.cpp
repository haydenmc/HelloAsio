#include "pch.h"

namespace
{
    constexpr uint16_t c_portNumber{ 55555 };
}

asio::awaitable<void> echo(asio::ip::tcp::socket socket)
{
    try
    {
        std::array<char, 1024> data;
        while (true)
        {
            std::size_t n{ co_await socket.async_read_some(asio::buffer(data), asio::use_awaitable) };
            co_await async_write(socket, asio::buffer(data, n), asio::use_awaitable);
        }
    }
    catch (std::exception const& e)
    {
        std::printf("echo exception: %s\n", e.what());
    }
}

asio::awaitable<void> listener()
{
    auto executor{ co_await asio::this_coro::executor };
    asio::ip::tcp::acceptor acceptor{ executor,
        asio::ip::tcp::endpoint{ asio::ip::tcp::v4(), c_portNumber } };
    while (true)
    {
        asio::ip::tcp::socket socket{ co_await acceptor.async_accept(asio::use_awaitable) };
        asio::co_spawn(executor, echo(std::move(socket)), asio::detached);
    }
}

int main()
{
    try
    {
        asio::io_context ioContext{ 1 };
        asio::signal_set signals{ ioContext, SIGINT, SIGTERM };
        signals.async_wait([&](auto, auto) { ioContext.stop(); });

        asio::co_spawn(ioContext, listener(), asio::detached);

        ioContext.run();
    }
    catch (std::exception const& e)
    {
        std::printf("Exception: %s\n", e.what());
    }
    return 0;
}
