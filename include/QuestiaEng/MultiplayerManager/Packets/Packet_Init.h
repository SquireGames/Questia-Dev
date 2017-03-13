#ifndef PACKET_INIT_H
#define PACKET_INIT_H

#include <string>
#include <SFML/Network.hpp>
#include "QuestiaEng/MultiplayerManager/UPacket.h"

enum class pktInitCommands {error = 0, server_info = 1};

struct Packet_Init
{
    Packet_Init();
    ~Packet_Init();
};

//{ client tcp init
struct Packet_Init_Tcp
{
    Packet_Init_Tcp(std::string _clientIP_local, std::string _clientIP_public, unsigned short _port_send, unsigned short _port_receive):
        clientIP_local(_clientIP_local)
        , clientIP_public(_clientIP_public)
        , port_send(_port_send)
        , port_receive(_port_receive)
    {}
    Packet_Init_Tcp() {}
    //variables
    std::string clientIP_local;
    std::string clientIP_public;
    unsigned short port_send;
    unsigned short port_receive;
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Init_Tcp& client)
{
    packet << static_cast <sf::Int32> (pkt::Header::clientTcp);
    packet << client.clientIP_local;
    packet << client.clientIP_public;
    packet << client.port_send;
    packet << client.port_receive;
    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Init_Tcp& client)
{
    packet >> client.clientIP_local;
    packet >> client.clientIP_public;
    packet >> client.port_send;
    packet >> client.port_receive;
    return packet;
}
//}

//{ client login
struct Packet_Init_Login
{
    Packet_Init_Login(std::string _username, std::string _password):
        username(_username)
        , password(_password)
    {}
    Packet_Init_Login() {}
    //will be encrypted later
    std::string username;
    std::string password;
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Init_Login& player)
{
    packet << static_cast <sf::Int32> (pkt::Header::clientLogin);
    packet << player.username;
    packet << player.password;
    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Init_Login& player)
{
    packet >> player.username;
    packet >> player.password;
    return packet;
}
//}

//{ server response
struct Packet_Init_SvrResp
{
    Packet_Init_SvrResp(bool _response):
        response(_response)
    {}
    Packet_Init_SvrResp() {}
    bool response;
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Init_SvrResp& player)
{
    packet << static_cast <sf::Int32> (pkt::Header::svrResp);
    packet << player.response;
    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Init_SvrResp& player)
{
    packet >> player.response;
    return packet;
}
//}

#endif // PACKET_INIT_H
