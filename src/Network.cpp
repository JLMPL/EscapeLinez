#include "Network.hpp"
#include <iostream>

MySocket		MySocketLogin;
MySocket		MySocketTime;
MySocket		MySocketPlayers;
MySocket		MySocketToBattle;

const int		*ClientId;

const std::vector<server> servers =
{
	server("Login Server", sf::IpAddress("serwerkrolak.ddns.net")),
	server("Loop Back", sf::IpAddress("127.0.0.1")),
};

void MySocket::send(std::string ToSend)
{
    socket.send(ToSend.c_str(), ToSend.length() + 1);
}

std::string MySocket::get()
{
	char message[128];
    std::size_t received;
    socket.receive(message, 128, received);
	std::string str = message;
    return str.substr(0, received);
}

int MySocket::getStatus()
{
    return status;
}
