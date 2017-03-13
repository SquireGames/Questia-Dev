#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include "QuestiaEng/Engine.h"

class Application
{
public:
	//ctor + dtor
    Application();
    ~Application();
	
	//start of the application
    void run();
	
private:
	Engine eng;
};
#endif // APPLICATION_H
