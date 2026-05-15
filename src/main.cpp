#include "Application.hpp"

int main(int argc, char** argv)
{
    memdb::server::Application application;
    return application.run();
}