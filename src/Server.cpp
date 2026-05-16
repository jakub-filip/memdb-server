#include "Server.hpp"

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace memdb::server
{
    void Server::start()
    {
        serverSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (serverSocket_ == INVALID_SOCKET)
        {
            throw std::runtime_error("Socket creation failed.");
        }

        u_long socketMode = 1;

        if (ioctlsocket(serverSocket_, FIONBIO, &socketMode) != NO_ERROR)
        {
            cleanup();

            throw std::runtime_error("ioctlsocket failed.");
        }

        SOCKADDR_IN serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        serverAddress.sin_port = htons(9000);

        if (bind(serverSocket_, reinterpret_cast<const SOCKADDR*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
        {
            cleanup();

            throw std::runtime_error("Bind failed.");
        }

        if (listen(serverSocket_, 50) == SOCKET_ERROR)
        {
            cleanup();

            throw std::runtime_error("Listen failed.");
        }
    }

    void Server::run()
    {
        running_ = true;

        while (running_)
        {
            SOCKET newClientSocket = accept(serverSocket_, nullptr, nullptr);

            if (newClientSocket != INVALID_SOCKET)
            {
                clientSockets_.push_back(newClientSocket);
            }

            for (auto clientSocketIt = clientSockets_.begin(); clientSocketIt != clientSockets_.end();)
            {
                char buffer[1024]{};

                int recvResult = recv(*clientSocketIt, buffer, 1024, 0);

                if (recvResult > 0)
                {
                    std::cout << buffer << std::endl;
                    ++clientSocketIt;
                }
                else if (recvResult == 0)
                {
                    closesocket(*clientSocketIt);
                    clientSocketIt = clientSockets_.erase(clientSocketIt);
                }
                else
                {
                    if (WSAGetLastError() != WSAEWOULDBLOCK)
                    {
                        closesocket(*clientSocketIt);
                        clientSocketIt = clientSockets_.erase(clientSocketIt);
                    }
                    else
                    {
                        ++clientSocketIt;
                    }
                }
            }
        }

        cleanup();
    }

    void Server::stop()
    {
        running_ = false;
    }

    void Server::cleanup() noexcept
    {
        for (SOCKET& clientSocket : clientSockets_)
        {
            closesocket(clientSocket);
        }

        clientSockets_.clear();

        closesocket(serverSocket_);
    }

    Server::~Server()
    {
        cleanup();
    }
}
