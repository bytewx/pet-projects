#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "HttpRequest.hpp"

#include <unordered_map>
#include <functional>

class Router 
{
public:
    using Handler = std::function<std::string(const HttpRequest&)>;

    void addRoute(const std::string& method, const std::string& path, Handler handler) 
    {
        routes[method + " " + path] = handler;
    }

    std::string handle(const HttpRequest& req) const 
    {
        auto it{ routes.find(req.method + " " + req.path) };

        if (it != routes.end()) 
        {
            return it->second(req);
        }

        return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
    }

private:
    std::unordered_map<std::string, Handler> routes;
};

#endif
