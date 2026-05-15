#ifndef MEMDB_SERVER_APPLICATION_HPP
#define MEMDB_SERVER_APPLICATION_HPP

namespace memdb::server
{
    class Application
    {
    public:
        [[nodiscard]] int run();
    };
}

#endif
