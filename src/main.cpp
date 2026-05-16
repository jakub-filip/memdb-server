#include "Application.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        memdb::server::Application application;
        application.run();

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
}