#include "ServerSocket.hpp"

#include <stdexcept>
#include <cstdint>

namespace memdb::server
{
    ServerSocket::ServerSocket()
    {
        if ((socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
            throw std::runtime_error("Socket creation failed.");
        }

        u_long socketMode{1};

        if (ioctlsocket(socket_, FIONBIO, &socketMode) != NO_ERROR)
        {
            closesocket(socket_);
            socket_ = INVALID_SOCKET;

            throw std::runtime_error("ioctlsocket failed.");
        }
    }

    ServerSocket::~ServerSocket()
    {
        closesocket(socket_);
        socket_ = INVALID_SOCKET;
    }

    void ServerSocket::bind(const std::string& ipAddress, uint16_t port)
    {
        SOCKADDR_IN serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        serverAddress.sin_port = htons(port);

        if (::bind(socket_, reinterpret_cast<SOCKADDR*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
        {
            throw std::runtime_error("bind failed.");
        }
    }

    void ServerSocket::listen(int backlog)
    {
        if (::listen(socket_, backlog) == SOCKET_ERROR)
        {
            throw std::runtime_error("listen failed.");
        }
    }

    std::optional<ClientSocket> ServerSocket::accept()
    {
        SOCKET clientSocket = ::accept(socket_, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                return std::nullopt;
            }

            throw std::runtime_error("accept failed.");
        }

        return ClientSocket(clientSocket);
    }
}
