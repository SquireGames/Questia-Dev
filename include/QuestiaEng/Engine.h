#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Font.hpp"

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiHandler.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"
#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/TileEngine/TileEngine_Editor.h"
#include "QuestiaEng/EntityManager/EntityManager.h"
#include "QuestiaEng/StateManager/StateManager.h"

#include "QuestiaEng/SV_Options.h"

#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/Controls/MouseListener.h"

class Engine
{
public:
	//ctor + dtor
	Engine(std::string windowName, int tickRate, int majorVersion, int minorVersion, int revision, std::string versionSuffix);
	~Engine() = default;

	//runtime loop function
	bool run();
	bool tick();
	void processInput();
	void render();

	//used in a state
	void terminate() {toTerminate = true;}

	//input
	MouseListener& 		mouse() 	{return mouseListener;}
	ctr::Input			lastKey()	{return lastInput;}

	//interfaces
	sf::RenderWindow&   win()   {return window;}
	ResourceManager& 	res() 	{return resourceManager;}
	GuiManager&			gui() 	{return guiManager;}
	GuiHandler& 		guiH()	{return guiHandler;}
	GuiLoader& 			guiLd() {return guiLoader;}
	TileEngine&	 		tile()	{return tileEngine;}
	TileEngine_Editor&	tileEd(){return tileEngineEditor;}
	EntityManager& 		ent()	{return entityManager;}
	StateManager& 		state() {return stateManager;}
	SV_Options& 		sv() 	{return saveFile;}
	
	//versions
	std::string getVersion();
	std::string getVersion_eng();
	
	void fixWindowScale();

private:
	//options
	SV_Options saveFile;

	//main window
	sf::RenderWindow window;
	utl::Vector2ui size_real;
	utl::Vector2ui size_scaled;
	utl::Vector2f scaleFactor;
	utl::Vector2f mousePos;

	//input
	MouseListener mouseListener;

	//manager
	ResourceManager resourceManager;
	GuiManager guiManager;
	GuiHandler guiHandler;
	GuiLoader guiLoader;
	TileEngine tileEngine;
	TileEngine_Editor tileEngineEditor;
	EntityManager entityManager;
	StateManager stateManager;

	//input buffer
	//saved as a char32_t to easily only allow ranges of unicode
	std::u32string inputBuffer;
	
	//most recent input method (e.g. for key binding)
	ctr::Input lastInput = ctr::Input::None;

	//timing
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time timeSinceLastTick;

	//flags
	bool toTerminate = false;
	
	//app version
	int majorVersion, minorVersion, revision;
	std::string versionSuffix;
	//eng version
	const int majorVersion_eng = 1, minorVersion_eng = 0, revision_eng = 0;
	std::string versionSuffix_eng = "Alpha";
};

#endif // ENGINE_H
