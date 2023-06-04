#include <http/HttpServer.hpp>

#include <boost/lexical_cast.hpp>

#include <iostream>



static constexpr std::string_view _default_server_address = "127.0.0.1";
static constexpr uint16_t _default_server_port = 80;

static constexpr std::string_view _default_server_document_root = "C:/Users/User/MyProjects/HttpServer/res";
static constexpr std::string_view _default_server_log_root = "C:/Users/User/MyProjects/HttpServer/log";



int main(int argc, char** argv)
{
    std::string _address = _default_server_address.data();
    uint16_t _port = _default_server_port;

    std::string _document_root = _default_server_document_root.data();
    std::string _log_root = _default_server_log_root.data();

    std::cout << "http_server.exe <address> <port> <path to document root> <path to log root>\n\n";



    switch (argc)
    {
    case 5:
        _log_root = argv[4];
        [[fallthrough]];
    case 4:
        _document_root = argv[3];
        [[fallthrough]];
    case 3:
        _port = boost::lexical_cast<uint16_t>(argv[2]);
        [[fallthrough]];
    case 2:
        _address = argv[1];
    }



    try
    {
        http::http_server _server(_address, _port, _document_root, _log_root);

        _server.run();
    }
    catch (const std::exception& _ex)
    {
        std::cerr << "ERROR: " << _ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "ERROR: Fatal error, server is finished.";
        return EXIT_FAILURE;
    }

    return 0;
}
