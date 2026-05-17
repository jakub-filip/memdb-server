#include "Server.hpp"

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace memdb::server
{
    Server::~Server()
    {
        cleanup();
    }

    void Server::start()
    {
        serverSocket_.bind("127.0.0.1", 9000);
        serverSocket_.listen(100);
    }

    void Server::run()
    {
        running_ = true;

        while (running_)
        {
            if (std::optional<ClientSocket> newClientSocket = serverSocket_.accept())
            {
                clientSockets_.emplace_back(std::move(*newClientSocket));
            }

            for (auto clientSocketIt = clientSockets_.begin(); clientSocketIt != clientSockets_.end();)
            {
                char buffer[1024]{};

                int recvResult = recv(clientSocketIt->getSocket(), buffer, 1024, 0);

                if (recvResult > 0)
                {
                    std::cout << buffer << std::endl;
                    ++clientSocketIt;
                }
                else if (recvResult == 0)
                {
                    closesocket(clientSocketIt->getSocket());
                    clientSocketIt = clientSockets_.erase(clientSocketIt);
                }
                else
                {
                    if (WSAGetLastError() != WSAEWOULDBLOCK)
                    {
                        closesocket(clientSocketIt->getSocket());
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
        for (ClientSocket& clientSocket : clientSockets_)
        {
            closesocket(clientSocket.getSocket());
        }

        clientSockets_.clear();
    }
}
