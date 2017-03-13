#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <map>

#include "QuestiaEng/EntityManager/EntityManager.h"

#include "QuestiaEng/MultiplayerManager/Server.h"

#include "QuestiaEng/MultiplayerManager/UPacket.h"
#include "QuestiaEng/MultiplayerManager/Packets/Packet_Player.h"

class MultiplayerManager
{
public:
    MultiplayerManager(std::string _serverName);
    ~MultiplayerManager();

///server
    void startHostingServer();
    void terminateHost();

    void host_changeTickRate(float _tickRate);
    std::string getPublicIP();
    std::string getLocalIP();


///client
    bool joinServer(std::string ipAddress);
    void terminateClient();

    void sendData(EntityManager& entityManager);
    void receiveData(EntityManager& entityManager);

///manager
    void update();

    bool isServerDead();
    bool isClientDead();


private:
///Threads
    //handles sending
    void host_sendThread();
    //handles receiving
    void host_receiveThread();
    // used to receive
    void client_mainThread();

///client commands
    bool client_init_testUDP();


///server vars
    Server* server;
    //terminate
    sf::Mutex host_terminateMutex;
    bool      host_terminate;
    //check if alive
    sf::Mutex host_aliveMutex;
    bool      host_alive_send;
    bool      host_alive_receive;
    //tick rate
    sf::Mutex host_changeTickRateMutex;
    bool      host_tickChange;
    float     tickRate;
    //threads
    sf::Thread thread_host_send;
    sf::Thread thread_host_receive;
    //thread safe
    bool isRunningServer;
    bool isKillingServer;


///client vars
//terminate
    sf::Mutex   client_terminateMutex;
    bool        client_terminate;
//check if alive
    sf::Mutex   client_aliveMutex;
    bool        client_alive;
//threads
    sf::Thread thread_client_main;
//tick
    int client_tempTick;
//thread safe
    bool isRunningClient;
    bool isKillingClient;

//socket
    sf::UdpSocket client_udpSocket_send;
    sf::UdpSocket client_udpSocket_receive;
    sf::TcpSocket client_tcpSocket_send;
    sf::TcpSocket client_tcpSocket_receive;
//player packet
    sf::Mutex playerDataMutex;
    std::vector <Packet_Player> playerData_received;
    std::queue  <Packet_Player> playerData_queue;
//entity manager
    sf::Mutex entityManagerMutex;
};

#endif // MULTIPLAYERMANAGER_H
