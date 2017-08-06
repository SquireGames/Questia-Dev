#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include "SFML/Graphics/Text.hpp"

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/Button.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/Logger.h"
#include "QuestiaEng/Utl/Savefile.h"

class GuiLoader;

class GuiBuilder
{
public:
	GuiBuilder(sf::RenderWindow& window, ResourceManager& resourceManager, GuiLoader& guiLoader
	           , std::vector<Button>& buttons, std::vector <Button*>& orderedDrawnButtons
	           , std::unordered_map<std::string, int>& buttonIDs) noexcept;
	GuiBuilder(GuiBuilder&&) noexcept = default;
	GuiBuilder& operator= (GuiBuilder&&) noexcept = default;
	~GuiBuilder() noexcept = default;

	GuiBuilder(const GuiBuilder&) = delete;
	GuiBuilder& operator= (const GuiBuilder&) = delete;

	//resets all buttons and the guiLoader
	void purgeButtons() noexcept;

	//must be set to use text, no default font upon initialization
	void setFont(sf::Font buttonFont) noexcept;
	sf::Font& getFont() noexcept;

	//if the per language (keyword -> text) feature is to be used, set a language, not set by default
	void setLang(std::string lang) noexcept;
	//TODO Have different context's for different categories, aka gui, items..
	std::u32string getText(const std::string& key) const noexcept;
	
	
	///GUI editor interface:
	
	///in place of exceptions, users should verify the existence of various gui elements, esp. if loading from a gui file
	///running in debug mode will log what check failed
	
	bool existsButton(const std::string& buttonName) const noexcept;
	bool existsButtonTemplate(const std::string& buttonName) const noexcept;
	bool existsButtonAtr(const std::string& buttonName, gui::BtnAtr atr, const std::string& atrName) const noexcept;
	bool existsGroup(const std::string& groupName) const noexcept;
	bool existsGroupTemplate(const std::string& groupName) const noexcept;
	//also verifies if button exists
	bool existsInGroup(const std::string& groupName, const std::string& buttonName) const noexcept;
	bool existsInGroupTemplate(const std::string& groupName, const std::string& buttonName) const noexcept;
	bool existsList(const std::string& listName) const noexcept;
	bool existsListGroup(const std::string& listName, const std::string& groupName) const noexcept;

	///the following are all commands to edit gui elements. in release mode, they assume that everything works and will probably
	///segfault if used incorrectly (thats why you should use exists*() functions to check the validity of the buttons). in debug mode it
	///will never crash and will log what function failed under the given parameters
	
	//allocates a new button, places in draw list
	void createButton(const std::string& buttonName, int layer = 1) noexcept;
	void createButton(const std::string& copyName, const std::string& originalName) noexcept;
	//links the alias name to the button referenced to by buttonName
	[[deprecated("Prefer to use: void createAlias(const std::string& alias, int buttonID)")]]
	void createAlias(const std::string& alias, const std::string& buttonName) noexcept;
	//links the alias name to a button with the specified ID
	void createAlias(const std::string& alias, int buttonID) noexcept;
	//allocates an undrawn button to be copied into 'real' buttons
	void createButtonTemplate(const std::string& buttonName, int layer = 1) noexcept;
	void createButtonTemplate(const std::string& copyName, const std::string& originalName) noexcept;

	//adds a new button element to the last referenced/created button
	void createBtnAtr(const std::string& atrName, gui::BtnAtr buttonAtr) noexcept;
	//adds a new button element to the button referenced by buttonName
	void createBtnAtr(const std::string& buttonName, const std::string& atrName, gui::BtnAtr buttonAtr) noexcept;
	//adds a new button element to the button referenced by buttonID
	void createBtnAtr(int buttonID, const std::string& atrName, gui::BtnAtr buttonAtr) noexcept;

	//changes the layer of the last referenced button
	void setButtonLayer(int layer) noexcept;
	//changes the layer of the button referenced by buttonName
	void setButtonLayer(const std::string& buttonName, int layer) noexcept;
	//changes the layer of the button referenced by buttonID
	void setButtonLayer(int buttonID, int layer) noexcept;

	//creates a grouping of buttons, to allow calling the same transformations on all group elements
	void createGroup(const std::string& groupName) noexcept;
	//creates a group that only holds button templates, can only be copied to real groups
	void createGroupTemplate(const std::string& groupName) noexcept;
	//copies a group template into a real group
	void createGroupFromTemplate(const std::string& groupName, const std::string& templateName) noexcept;

	//adds buttons to groups and button templates to group templates for the last referenced group
	void addToGroup(const std::string& entryName) noexcept;
	//adds buttons to groups and button templates to group templates for a specific group
	void addToGroup(const std::string& groupName, const std::string& entryName) noexcept;

	//returns the button name of a button from a derived group given the original group template's button template entry name
	[[deprecated("Prefer to use: int getGroupEntryID(const std::string& groupName, const std::string& buttonName)")]]
	std::string getGroupEntry(const std::string& groupName, const std::string& buttonName) const noexcept;
	//returns the button ID of a button from a derived group given the original group template's button template entry name
	int getGroupEntryID(const std::string& groupName, const std::string& buttonName) const noexcept;;

	//a structure for allowing evenly spaced groups from a specified group template
	void createList(const std::string& listName) noexcept;

	//specifies the group template for the last modified/created list
	void setListTemplate(const std::string& groupTemplate) noexcept;
	//specifies the group template for a list
	void setListTemplate(const std::string& listName, const std::string& groupTemplate) noexcept;
	//specifies the list spacing for the last modified/created list
	void setListSpacing(int spacing_x, int spacing_y) noexcept;
	//specifies the list spacing for a list
	void setListSpacing(const std::string& listName, int spacing_x, int spacing_y) noexcept;
	//specifies the list origin for the last modified/created list
	void setListPosition(std::pair<int, int> position) noexcept;
	//specifies the list origin for a list
	void setListPosition(const std::string& listName, std::pair<int, int> position) noexcept;
	
	//creates a list entry by duplicating the specified group template for the last modified list
	std::string createListEntry() noexcept;
	//creates a list entry by duplicating the specified group template for a specific list
	std::string createListEntry(const std::string& listName) noexcept;

	//modifies properties of a button
	template <class T> void setButton(gui::BtnChar buttonChar, T value) noexcept;
	template <class T> void setButton(int buttonID, gui::BtnChar buttonChar, T value) noexcept;
	template <class T> void setButton(const std::string& buttonName, gui::BtnChar buttonChar, T value) noexcept;

	//modifies properties of a button attribute
	template <class T> void setBtnAtr(gui::BtnAtrChar atrChar, T value) noexcept;
	template <class T> void setBtnAtr(int buttonID, const std::string& atrName, gui::BtnAtrChar atrChar, T value) noexcept;
	template <class T> void setBtnAtr(const std::string& buttonName, const std::string& atrName, gui::BtnAtrChar atrChar, T value) noexcept;

	//modifies a property of every button within a group
	template <class T> void setGroupAtr(gui::BtnChar buttonChar, T value) noexcept;
	template <class T> void setGroupAtr(const std::string& groupName, gui::BtnChar buttonChar, T value) noexcept;

	//modifies the button property of every button in every group of a list
	template <class T> void setListAtr(gui::BtnChar buttonChar, T value);
	template <class T> void setListAtr(const std::string& listName, gui::BtnChar buttonChar, T value) noexcept;

	//removes the element, along with everything it contains
	void deleteList(const std::string& listName) noexcept;
	void deleteGroup(const std::string& groupName) noexcept;
	void deleteButton(const std::string& buttonName) noexcept;
	void deleteButton(int buttonID) noexcept;

private:
	struct ListData
	{
		ListData(std::string name):listName(name) {}
		std::string listName;
		std::string groupTemplate = std::string();
		std::pair<int, int> position = std::make_pair(0,0);
		std::pair<int, int> listSpacing = std::make_pair(0,100);
		std::vector<std::string> groups;
	};

	//generates a button ID, saved pair as a hash in buttonIDs
	int getNewID(const std::string& buttonName) noexcept;
	//creates a button, returns a reference to the button
	Button& emplaceButton(bool isTemplate, const std::string& buttonName, int templateID = -1) noexcept;
	//copies the given button to a new one, returns a reference to the button
	Button& copyButton(Button& old, const std::string& buttonName, int templateID = -1) noexcept;

	//returns the position in the buttons vector with the given ID, or -1 if it does not exist
	int getPos(int buttonID) const noexcept;
	//returns the position in the buttons vector with the given name, or -1 if it does not exist
	template<class String, typename = typename std::enable_if<std::is_constructible<std::string, String>::value>::type>
	int getPos(String&& name) const noexcept;

	//get the ID's that belong to the group entry
	const std::vector<int>& getGroupIDs(const std::string& groupName) const noexcept;
	std::vector<int>& getGroupIDs(const std::string& groupName) noexcept;
	//get the ListData given a listName
	const ListData& getList(const std::string& listName) const noexcept;
	ListData& getList(const std::string& listName) noexcept;
	
	//used only once per visible button
	void placeInDrawList(Button* button) noexcept;
	//only to be used when button storage is modified
	void refreshDrawVector() noexcept;
	
	
	//all replacable button indecies
	std::vector<int> unusedPos;
	//holds all groups and group template compositions
	std::vector<std::pair<std::string, std::vector<int> > > groups;
#ifdef DEBUGMODE
	//holds names of all group templates, only for debugging
	std::vector<std::string> groupTemplates;
#endif
	std::vector<ListData> lists;

	sf::RenderWindow& window;
	ResourceManager& resourceManager;
	GuiLoader& guiLoader;
	std::vector<Button>& buttons;
	std::vector <Button*>& orderedDrawnButtons;
	std::unordered_map<std::string, int>& buttonIDs;

	//button ID's are sequentially given, starting from 0
	int buttonCount = 0;

	//the most recently addressed element
	int lastButton = -1;
	std::string lastBtnAtr;
	std::string lastGroup;
	std::string lastList;

	sf::Font buttonFont;
	std::string lang;
	std::vector<std::pair<std::u32string, std::u32string>> langPairs;

	//holds drawing order of buttons, by buttonID
	std::vector<int> visibleButtonIDs;
};

template <class T>
void GuiBuilder::setButton(gui::BtnChar buttonChar, T value) noexcept
{
	setButton(lastButton, buttonChar, value);
}
template <class T>
void GuiBuilder::setButton(int buttonID, gui::BtnChar buttonChar, T value) noexcept
{
#ifdef DEBUGMODE
	if(getPos(buttonID) == -1)
	{
		LOG("Button with ID: " + std::to_string(buttonID) + " does not exist");
		return;
	}
#endif
	buttons.at(getPos(buttonID)).setButton(buttonChar, value);
}
template <class T>
void GuiBuilder::setButton(const std::string& buttonName, gui::BtnChar buttonChar, T value) noexcept
{
#ifdef DEBUGMODE
	if(getPos(buttonName) == -1)
	{
		LOG("Button with name: '" + buttonName + "' does not exist");
		return;
	}
#endif
	buttons.at(getPos(buttonName)).setButton(buttonChar, value);
}

template <class T>
void GuiBuilder::setBtnAtr(gui::BtnAtrChar atrChar, T value) noexcept
{
	setBtnAtr(lastButton, lastBtnAtr, atrChar, value);
}
template <class T>
void GuiBuilder::setBtnAtr(int buttonID, const std::string& atrName, gui::BtnAtrChar atrChar, T value) noexcept
{
#ifdef DEBUGMODE
	if(getPos(buttonID) == -1)
	{
		LOG("Button with ID: " + std::to_string(buttonID) + " does not exist");
		return;
	}
#endif
	buttons.at(getPos(buttonID)).setBtnAtr(atrName, atrChar, value);
}
template <class T>
void GuiBuilder::setBtnAtr(const std::string& buttonName, const std::string& atrName, gui::BtnAtrChar atrChar, T value) noexcept
{
#ifdef DEBUGMODE
	if(getPos(buttonName) == -1)
	{
		LOG("Button with name: '" + buttonName + "' does not exist");
		return;
	}
#endif
	buttons.at(getPos(buttonName)).setBtnAtr(atrName, atrChar, value);
}

template <class T>
void GuiBuilder::setGroupAtr(gui::BtnChar buttonChar, T value) noexcept
{
	setGroupAtr(lastGroup, buttonChar, value);
}
template <class T>
void GuiBuilder::setGroupAtr(const std::string& groupName, gui::BtnChar buttonChar, T value) noexcept
{
#ifdef DEBUGMODE
	if(!existsGroup(groupName))
	{
		LOG("Group with name: '" + groupName + "' does not exist");
		return;
	}
#endif
	if(buttonChar == gui::BtnChar::coords)
	{
		buttonChar = gui::BtnChar::coords_group;
	}
	std::vector<int>& ids = getGroupIDs(groupName);
	for(int id : ids)
	{
		buttons.at(getPos(id)).setButton(buttonChar, value);
	}
}

template <class T>
void GuiBuilder::setListAtr(gui::BtnChar buttonChar, T value)
{
	setListAtr(lastList, buttonChar, value);
}
template <class T>
void GuiBuilder::setListAtr(const std::string& listName, gui::BtnChar buttonChar, T value) noexcept
{
#ifdef DEBUGMODE
	if(!existsList(listName))
	{
		LOG("List with name: '" + listName + "' does not exist");
		return;
	}
#endif
	ListData& list = getList(listName);
	for(const std::string& groupIt : list.groups)
	{
		setGroupAtr(groupIt, buttonChar, value);
	}
}

template<class String, typename = typename std::enable_if<std::is_constructible<std::string, String>::value>::type>
inline int GuiBuilder::getPos(String&& name) const noexcept
{
#ifdef DEBUGMODE
	if(!buttonIDs.count(name))
	{
		return -1;
	}
#endif
	return(getPos(buttonIDs.at(std::forward<String>(name))));
}

#endif // GUIBUILDER_H
