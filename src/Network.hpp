/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Network.hpp
 * Author: krzysiek
 *
 * Created on October 30, 2018, 2:38 PM
 */

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <SFML/Network.hpp>
#include <string>


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


#endif /* NETWORK_HPP */
