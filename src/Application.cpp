#include "Application.hpp"

namespace memdb::server
{
    void Application::run()
    {
        server_.start();
        serverThread_ = std::thread(&Server::run, &server_);

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(10));

            break;
        }

        server_.stop();

        if (serverThread_.joinable())
        {
            serverThread_.join();
        }
    }
}
