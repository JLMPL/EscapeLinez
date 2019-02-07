/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Network.cpp
 * Author: krzysiek
 * 
 * Created on October 30, 2018, 2:38 PM
 */

#include "Network.hpp"
#include <iostream>

MySocket		MySocketLogin;
MySocket		MySocketTime;
MySocket		MySocketPlayers;
MySocket		MySocketToBattle;
const int		*ClientId;




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
