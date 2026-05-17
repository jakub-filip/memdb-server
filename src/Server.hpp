#ifndef MEMDB_SERVER_SERVER_HPP
#define MEMDB_SERVER_SERVER_HPP

#include "ServerSocket.hpp"

#include <atomic>
#include <vector>

namespace memdb::server
{
    class Server
    {
    public:
        ~Server();
        void start();
        void run();
        void stop();

    private:
        std::atomic_bool running_{false};

        ServerSocket serverSocket_;

        std::vector<ClientSocket> clientSockets_;

        void cleanup() noexcept;
    };
}

#endif
