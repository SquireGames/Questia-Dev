#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include "QuestiaEng/Utl/Logger.h"

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/Button.h"
#include "QuestiaEng/Utl/Type/Vector2.h"

#include "QuestiaEng/GuiManager/GuiLoader.h"
#include "QuestiaEng/GuiManager/GuiBuilder.h"

class GuiManager
{
public:
	GuiManager(sf::RenderWindow& window, ResourceManager& resourceManager) noexcept;
	GuiManager(GuiManager&&) noexcept = default;
	GuiManager& operator= (GuiManager&&) noexcept = default;
	~GuiManager() noexcept = default;

	GuiManager(const GuiManager&) = delete;
	GuiManager& operator= (const GuiManager&) = delete;

	GuiBuilder& edit() noexcept;

	//sets a folder to use to load gui's from, "Default" by default
	void setGuiPack(const std::string& guiPack);
	//loads a gui from a file in the gui pack directory, will fall back to find the gui in Default if it does not exist
	void loadGui(const std::string& gui);

	template<class String, typename = typename std::enable_if<std::is_constructible<std::string, String>::value>::type>
	bool isHovered(String&& buttonName) const noexcept;
	bool isHovered(int buttonID) const noexcept;
	void draw() noexcept;

	///to be called by Engine every tick (not necessary for states to call in update function):
	void setMousePosition(utl::Vector2f mouseCoords) noexcept;

private:
	const Button* const getButton(int buttonID) const noexcept;
	template<class String, typename = typename std::enable_if<std::is_constructible<std::string, String>::value>::type>
	const Button* const getButton(String&& name) const noexcept;

	sf::RenderWindow& window;
	ResourceManager& resourceManager;

	utl::Vector2f mouseCoords;

	std::vector<Button> buttons;
	std::vector<Button*> orderedDrawnButtons;
	//used to hash a button name to a buttonID
	std::unordered_map<std::string, int> buttonIDs;

	GuiLoader guiLoader;
	GuiBuilder guiBuilder;
};

template<class String, typename = typename std::enable_if<std::is_constructible<std::string, String>::value>::type>
inline bool GuiManager::isHovered(String&& buttonName) const noexcept
{
#ifdef DEBUGMODE
	if(getButton(buttonName) == nullptr)
	{
		LOG(std::string("Button with name: '") + buttonName + "' does not exist");
		return false;
	}
#endif
	return getButton(std::forward<String>(buttonName))->isHovered;
}

template<class String, typename = typename std::enable_if<std::is_constructible<std::string, String>::value>::type>
inline const Button* const GuiManager::getButton(String&& name) const noexcept
{
#ifdef DEBUGMODE
	if(!buttonIDs.count(name))
	{
		LOG(std::string("Button with name: '") + name + "' does not exist");
		return nullptr;
	}
#endif
	return(getButton(buttonIDs.at(std::forward<String>(name))));
}

#endif // GUIMANAGER_H
