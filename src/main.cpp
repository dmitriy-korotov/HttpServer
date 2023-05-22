#include "Defines.hpp"

#include "HttpServer.hpp"



int main(int argc, char** argv)
{
    boost::asio::io_context _io_context;

    http::HttpServer server(_io_context, 8000, "C:/Users/User/MyProjects/HttpServer/res");

    server.start();

    _io_context.run();

    return 0;
}