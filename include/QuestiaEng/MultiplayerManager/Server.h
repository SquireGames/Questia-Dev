#ifndef SERVER_H
#define SERVER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <queue>

#include "QuestiaEng/MultiplayerManager/UPacket.h"
#include "QuestiaEng/MultiplayerManager/Packets/Packet_Player.h"
#include "QuestiaEng/MultiplayerManager/Packets/Packet_Init.h"
#include "QuestiaEng/MultiplayerManager/Packets/Packet_Entity.h"

#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/EntityManager/EntityManager.h"

#include "QuestiaEng/ResourceManager/ResourceManager.h"

enum class ClientStage {disconnected = 0, connected = 1, choosingCharacter = 2, active = 3};

struct Client
{
    Client(int _clientID, sf::TcpSocket* _tcpSocket_send, sf::TcpSocket* _tcpSocket_receieve,  std::string _ip, unsigned short _port_udp_send, unsigned short _port_udp_receieve):
        clientID(_clientID)
        , tcpSocket_send(_tcpSocket_send)
        , tcpSocket_receieve(_tcpSocket_receieve)
        , ip(_ip)
        , port_udp_send (_port_udp_send)
        , port_udp_receieve (_port_udp_receieve)
        //, clientStage(ClientStage::disconnected)
    {}

    int clientID;

    sf::TcpSocket* tcpSocket_send;
    sf::TcpSocket* tcpSocket_receieve;

    std::string ip;
    unsigned short port_udp_send;
    unsigned short port_udp_receieve;

    ClientStage clientStage;

    //client connects -> client sends login info -> server returns character list -> client sends character choice -> server initiates character and starts sending info
};

struct Map
{
    Map():
        resourceManager()
        , window()
        , entityManager(resourceManager)
    {}

    //inactive
    ResourceManager resourceManager;
    sf::RenderWindow window;

    EntityManager entityManager;
};

class Server
{
public:
    Server();
    ~Server();

    ///send thread
    void update();
    void send();
    ///receive thread
    void receive();

private:
    ///server
    void checkClient(); //used for joining stages,

    ///clients
    //new clients
    std::vector <sf::TcpSocket*> toBeSortedTcp;
    //existing clients
    std::vector <Client*> clientVector;
    int clientCount;

    ///send
    sf::UdpSocket udpSocket_send;
    sf::TcpSocket tcpSocket;

    ///receive
    sf::UdpSocket udpSocket_receive;
    sf::SocketSelector selector;
    sf::TcpListener listener;

    ///data
    //player packet
    sf::Mutex playerDataMutex;
    std::vector <Packet_Player> playerData_received;
    std::queue  <Packet_Player> playerData_queue;
    //entityManager
    sf::Mutex entityManagerMutex;

    ///game
    std::vector <Map*> mapVector;

    ///login
    std::vector <std::pair <std::string, std::string> > registeredClients;

    unsigned int tick;
};

#endif // SERVER_H
