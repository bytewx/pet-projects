#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <unordered_map>
#include <sstream>

struct HttpRequest 
{
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    static HttpRequest parse(const std::string& raw) 
    {
        HttpRequest req;
        std::istringstream stream(raw);
        std::string line;

        if (std::getline(stream, line)) 
        {
            std::istringstream requestLine(line);

            requestLine >> req.method >> req.path;
        }

        while (std::getline(stream, line) && line != "\r") 
        {
            size_t colonPos{ line.find(':') };

            if (colonPos != std::string::npos) 
            {
                std::string key{ line.substr(0, colonPos) };
                std::string value{ line.substr(colonPos + 1) };

                key.erase(key.find_last_not_of(" \r") + 1);
                value.erase(0, value.find_first_not_of(" "));
                value.erase(value.find_last_not_of(" \r") + 1);

                req.headers[key] = value;
            }
        }
        
        req.body.assign(std::istreambuf_iterator<char>(stream), {});

        return req;
    }
};

#endif
