#include "ServerSocket.hpp"
#include "Router.hpp"
#include "HttpRequest.hpp"

int main() {
    try {
        Router router;

        router.addRoute("GET", "/", [](const HttpRequest& req) 
        {
            return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from GET /";
        });

        router.addRoute("POST", "/submit", [](const HttpRequest& req) 
        {
            return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nReceived POST body: " + req.body;
        });

        router.addRoute("PUT", "/update", [](const HttpRequest& req) 
        {
            return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nUpdated data: " + req.body;
        });

        auto& server{ ServerSocket::getInstance(8080) };

        server.listenLoop([&](const std::string& rawRequest) 
        {
            HttpRequest req = HttpRequest::parse(rawRequest);

            return router.handle(req);
        });

    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        
        return EXIT_FAILURE;
    }
}
