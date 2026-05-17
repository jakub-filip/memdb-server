#ifndef MEMDB_SERVER_SERVERSOCKET_HPP
#define MEMDB_SERVER_SERVERSOCKET_HPP

#include "ClientSocket.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <winsock2.h>

namespace memdb::server
{
    class ServerSocket
    {
    public:
        ServerSocket();
        ServerSocket(ServerSocket& serverSocket) = delete;
        ServerSocket& operator=(ServerSocket& serverSocket) = delete;
        ServerSocket(ServerSocket&& serverSocket) = delete;
        ServerSocket& operator=(ServerSocket&& serverSocket) = delete;
        ~ServerSocket();
        void bind(const std::string&, uint16_t);
        void listen(int);
        std::optional<ClientSocket> accept();

    private:
        SOCKET socket_{INVALID_SOCKET};
    };
}

#endif
