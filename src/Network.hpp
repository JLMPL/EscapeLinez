#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <SFML/Network.hpp>
#include <string>

enum SocketStatus
{
    SOCKET_STATUS_OK,
    SOCKET_STATUS_NOT_READY,
    SOCKET_STATUS_PARTIAL,
    SOCKET_STATUS_DISCONNECTED,
    SOCKET_STATUS_UNEXPECTED_ERROR
};

class MySocket
{
public:
    MySocket() = default;
    MySocket(sf::IpAddress ip, int port)
        : MySocketIp(ip), MySocketPort(port)
    {
        status = socket.connect(ip, port);
    }

    void send(std::string ToSend);
    std::string get();
    int getStatus();

private:
    sf::IpAddress MySocketIp;
    sf::TcpSocket socket;
    sf::Socket::Status status;
    int MySocketPort;
};

extern MySocket             MySocketLogin;
extern MySocket             MySocketTime;
extern MySocket             MySocketPlayers;
extern MySocket             MySocketToBattle;
extern const int            *ClientId;

struct server
{
    std::string name;
    sf::IpAddress ip;

    server(std::string name, sf::IpAddress ip) :
        name(name), ip(ip)
    {}
};

extern const std::vector<server> servers;

#endif /* NETWORK_HPP */
