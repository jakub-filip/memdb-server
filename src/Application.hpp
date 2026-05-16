#ifndef MEMDB_SERVER_APPLICATION_HPP
#define MEMDB_SERVER_APPLICATION_HPP

#include "Networking.hpp"
#include "Server.hpp"

#include <thread>

namespace memdb::server
{
    class Application
    {
    public:
        void run();

    private:
        Networking networking_;
        Server server_;
        std::thread serverThread_;
    };
}

#endif
