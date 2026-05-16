#include "Application.hpp"

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace memdb::server
{
    void Application::run()
    {
        initializeNetworking();

        try
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
        catch (const std::exception& e)
        {
            shutdownNetworking();

            throw;
        }

        shutdownNetworking();
    }

    void Application::initializeNetworking()
    {
        WSADATA wsaData{};

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            throw std::runtime_error("WSAStartup failed");
        }
    }

    void Application::shutdownNetworking() noexcept
    {
        WSACleanup();
    }
}
