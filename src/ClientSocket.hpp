#ifndef MEMDB_SERVER_CLIENTSOCKET_HPP
#define MEMDB_SERVER_CLIENTSOCKET_HPP

#include <winsock2.h>

namespace memdb::server
{
    class ClientSocket
    {
    public:
        explicit ClientSocket(SOCKET);
        ClientSocket(const ClientSocket&) = delete;
        ClientSocket& operator=(const ClientSocket&) = delete;
        ClientSocket(ClientSocket&&) noexcept;
        ClientSocket& operator=(ClientSocket&&) noexcept;
        SOCKET getSocket() const;
    private:
        SOCKET socket_{INVALID_SOCKET};
    };
}

#endif
