#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>	//std::function
#include <memory> 		//std::unique_ptr
#include <algorithm> 	//std::swap
#include <future>
#include <thread>
#include <chrono>

class State;
class Engine;

class StateManager
{
public:
	//ctor + dtor
	StateManager(Engine& eng);
	~StateManager();
	
	//registers state, only call this once per state
	void reg(std::string name, std::function<State*()> state);
	
	//adds state to top of state stack
	void pushState(std::string stateName);
	//queues deletion of top state (if any)
	void popState();
	//queues deletion of top state (if any), replaces with new state
	void changeState(std::string stateName);
	//queues deletion of top state (if any), draws loading state while changing to new state
	void transitionState(std::string newState, std::string loadingState);

	//state functions
	void sUpdate();
	void sProcessInput(std::string input);
	void sDisplay();
	
	//state functions
	void sUpdate_second();
	void sProcessInput_second(std::string input);
	void sDisplay_second();

private:
	//sees if there are states to be deleted
	void checkDelQueue();
	//does actual state deletion
	void deleteState(unsigned int index);
	
	//handles loading screen
	void checkLoading();

	//state containers
	std::vector<std::unique_ptr<State>> stateStack;
	std::map<std::string, std::function<State*()>> stateMap;
	
	//used to queue deletion
	bool isDelQueued = false;
	int delIndex = 0;
	
	//used for loading screen
	bool isStateLoading = false;
	State* newState = nullptr;
	std::thread loadingThread;
	std::promise<State*> thrPromise;
	std::future<State*> thrFuture;
	
	//is distributed to new states
	Engine& eng;
};

#endif // STATEMANAGER_H
