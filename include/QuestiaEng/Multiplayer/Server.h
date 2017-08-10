#ifndef SERVER_H
#define SERVER_H

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/EntityManager/EntityManager.h"

class Server
{
public:
	Server(std::string serverName = "Questia Server", int tickRate = 32, int threads = 4, unsigned short hostUDPPort = 7777, unsigned short hostTCPPort = 7778);
	~Server() = default;

	void startServer();
	void terminate();
	
private:
	std::string serverName;
	int tickRate;
	int threads;
	unsigned short hostUDPPort;
	unsigned short hostTCPPort;

	TileEngine tileEngine;
	EntityManager entityManager;
};

#endif // SERVER_H
