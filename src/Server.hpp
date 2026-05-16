#ifndef MEMDB_SERVER_SERVER_HPP
#define MEMDB_SERVER_SERVER_HPP

#include <atomic>
#include <vector>
#include <WinSock2.h>
#include <ws2tcpip.h>

namespace memdb::server
{
    class Server
    {
    public:
        void start();
        void run();
        void stop();
        ~Server();

    private:
        std::atomic_bool running_{false};

        SOCKET serverSocket_{INVALID_SOCKET};
        std::vector<SOCKET> clientSockets_;

        void cleanup() noexcept;
    };
}

#endif
