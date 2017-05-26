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
	//queues deletion of top state (if any), queues new state
	void changeState(std::string stateName);
	//queues transition, which pops top (if any) and loads new state on other thread
	//loadingState cannot use any texture loading operation
	void transitionState(std::string newState, std::string loadingState);

	//state functions
	void sUpdate();
	void sProcessInput(std::u32string& inputText);
	void sDisplay();

	//state functions
	void sUpdate(unsigned int offset);
	void sProcessInput(unsigned int offset, std::u32string& inputText);
	void sDisplay(unsigned int offset);

private:
	//sees if there are states to be deleted, made, or transitioned
	void checkQueues();
	//does actual state deletion, creation, transition
	void deleteState(unsigned int index);
	void createState(std::string stateName);
	void makeTransition(std::string newState, std::string loadingState);

	//handles loading screen
	void checkLoading();

	//holds index of highest state
	unsigned int stackIndex = -1;

	//state containers
	std::vector<std::unique_ptr<State>> stateStack;
	std::map<std::string, std::function<State*()>> stateMap;

	//used to queue deletion. new state, and transitions
	bool isDelQueued = false;
	bool isStateQueued = false;
	bool isTransitionQueued = false;
	int delIndex = 0;
	std::string newStateName;
	std::string newTransitionName;

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
