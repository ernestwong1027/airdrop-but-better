#include "server.hpp"
#include <iostream>

void create_server() {


    httplib::Server svr;
        svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
  res.set_content("Hello World!", "text/plain");
});

    // svr.Post("/multipart", [&](const auto& req, auto& res) {

    //     const auto& file = req.get_file_value("name1");
    //     std::cout << file.filename;
        
    //     // file.filename;
    //     // file.content_type;
    //     // file.content;
    // });

    svr.listen("0.0.0.0", 8080);

}

int main() {

    create_server();

    return 0;
}