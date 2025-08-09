#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <functional>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    using SocketType = SOCKET;
    #define CLOSESOCKET closesocket
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    using SocketType = int;
    #define CLOSESOCKET close
    #define INVALID_SOCKET (-1)
    #define SOCKET_ERROR   (-1)
#endif

inline std::string getFileContent(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open())
    {
        return "";
    }
        
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

inline std::string handleHttpRequest(const std::string& request) 
{
    size_t firstSpace{ request.find(' ') };
    size_t secondSpace{ request.find(' ', firstSpace + 1) };
    std::string path{ "/" };

    if (firstSpace != std::string::npos && secondSpace != std::string::npos) 
    {
        path = request.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    }

    if (path == "/")
    {
        path = "/index.html";
    }

    if (!path.empty() && path[0] == '/')
    {
        path.erase(0, 1);
    }

    std::string content = getFileContent(path);

    if (content.empty()) 
    {
        return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
    }

    std::string contentType{ "text/html" };

    if (path.find(".css") != std::string::npos)
    {
        contentType = "text/css";
    }
    else if (path.find(".js") != std::string::npos)
    {
        contentType = "application/javascript";
    }
    else if (path.find(".png") != std::string::npos)
    {
        contentType = "image/png";
    }

    return "HTTP/1.1 200 OK\r\nContent-Type: " + contentType + "\r\n\r\n" + content;
}

class ServerSocket 
{
public:
    static ServerSocket& getInstance(int port = 8080) 
    {
        static ServerSocket instance(port);
        return instance;
    }

    SocketType getSocket() const 
    { 
        return serverFD; 
    }

    void listenLoop(std::function<std::string(const std::string&)> requestHandler) 
    {
        sockaddr_in clientAddr{};
        socklen_t addrLen{ sizeof(clientAddr) };

        while (true) 
        {
            SocketType clientFD = accept(serverFD, (sockaddr*)&clientAddr, &addrLen);

            if (clientFD == INVALID_SOCKET) 
            {
                std::cerr << "Accept failed\n";
                
                continue;
            }

            char buffer[8192] = { 0 };
            int bytesReceived = recv(clientFD, buffer, sizeof(buffer), 0);

            if (bytesReceived > 0) 
            {
                std::string request(buffer, bytesReceived);
                std::string response = requestHandler(request);

                send(clientFD, response.c_str(), (int)response.size(), 0);
            }

            CLOSESOCKET(clientFD);
        }
    }

private:
    SocketType serverFD;

    ServerSocket(int port) 
    {
        initSockets();

        serverFD = socket(AF_INET, SOCK_STREAM, 0);

        if (serverFD == INVALID_SOCKET) 
        {
            cleanupSockets();

            throw std::runtime_error("Failed to create socket");
        }

        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        if (bind(serverFD, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) 
        {
            CLOSESOCKET(serverFD);
            cleanupSockets();

            throw std::runtime_error("Bind failed");
        }

        if (listen(serverFD, SOMAXCONN) == SOCKET_ERROR) 
        {
            CLOSESOCKET(serverFD);
            cleanupSockets();

            throw std::runtime_error("Listen failed");
        }

        std::cout << "Server listening on port " << port << "\n";
    }

    ~ServerSocket() 
    {
        CLOSESOCKET(serverFD);
        cleanupSockets();

        std::cout << "Server socket closed\n";
    }

    void initSockets() 
    {
        #ifdef _WIN32
            WSADATA wsaData;

            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            {
                throw std::runtime_error("WSAStartup failed");
            }
        #endif
    }

    void cleanupSockets() 
    {
        #ifdef _WIN32
            WSACleanup();
        #endif
    }

    ServerSocket(const ServerSocket&) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
};

#endif
