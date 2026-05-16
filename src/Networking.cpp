#include "Networking.hpp"

#include <stdexcept>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace memdb::server
{
    Networking::Networking()
    {
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            throw std::runtime_error("WSAStartup failed.");
        }
    }

    Networking::~Networking()
    {
        WSACleanup();
    }
}