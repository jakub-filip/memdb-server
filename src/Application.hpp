#ifndef MEMDB_SERVER_APPLICATION_HPP
#define MEMDB_SERVER_APPLICATION_HPP

#include "Server.hpp"

#include <thread>

namespace memdb::server
{
    class Application
    {
    public:
        void run();

    private:
        Server server_;
        std::thread serverThread_;

        void initializeNetworking();
        void shutdownNetworking() noexcept;
    };
}

#endif
