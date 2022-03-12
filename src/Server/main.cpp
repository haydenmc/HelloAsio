#include <asio.hpp>
#include <functional>
#include <iostream>

void print(const asio::error_code& /*e*/, asio::steady_timer* t, int* count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + asio::chrono::seconds{ 1 });
        t->async_wait(std::bind(print, std::placeholders::_1, t, count));
    }
}

asio::awaitable<void> listener()
{

}

int main()
{
    asio::io_context io;
    asio::co_spawn(io, listener(), asio::detached);
    int count{ 0 };
    asio::steady_timer t{ io, asio::chrono::seconds{1} };
    t.async_wait(std::bind(print, std::placeholders::_1, &t, &count));
    io.run();
    std::cout << "Final count is " << count << std::endl;
    return 0;
}
