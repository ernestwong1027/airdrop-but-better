#include "server.hpp"

void create_server(int port) {


    httplib::Server svr;

    httplib::SSLServer svr;

    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

}