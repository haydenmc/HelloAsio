#include "pch.h"
#include "Room.h"
#include "Listener.h"

namespace
{
    constexpr uint16_t c_portNumber{ 55555 };
}

int main()
{
    try
    {
        asio::thread_pool threadPool;
        
        asio::co_spawn(threadPool,
            [executor{ threadPool.get_executor() }]()->asio::awaitable<void>
            {
                auto room{ Room::Create(executor) };
                auto listener{ Listener::Create(executor, room, c_portNumber) };
                co_await listener->ListenAsync();
            },
            asio::detached);
        
        threadPool.join();
    }
    catch (std::exception const& e)
    {
        std::printf("Exception: %s\n", e.what());
    }
    return 0;
}
