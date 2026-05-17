#include "ClientSocket.hpp"

namespace memdb::server
{
    ClientSocket::ClientSocket(SOCKET socket) : socket_{socket} {}

    ClientSocket::ClientSocket(ClientSocket&& clientSocket) noexcept : socket_{clientSocket.socket_}
    {
        clientSocket.socket_ = INVALID_SOCKET;
    }

    ClientSocket& ClientSocket::operator=(ClientSocket&& clientSocket) noexcept
    {
        if (this != &clientSocket)
        {
            if (socket_ != INVALID_SOCKET)
            {
                closesocket(socket_);
            }

            socket_ = clientSocket.socket_;

            clientSocket.socket_ = INVALID_SOCKET;
        }

        return *this;
    }

    SOCKET ClientSocket::getSocket() const
    {
        return socket_;
    }
}
