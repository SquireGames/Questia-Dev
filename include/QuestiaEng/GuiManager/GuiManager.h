#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"

#include "QuestiaEng/Utl/Logger.h"

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/Button.h"
#include "QuestiaEng/Utl/Type/Vector2.h"

#include "QuestiaEng/Utl/Savefile.h"

class GuiManager
{
public:
	GuiManager(sf::RenderWindow& window, ResourceManager& resourceManager);
	~GuiManager();

	void setMousePosition(utl::Vector2f mouseCoords);

	bool isClicked(const std::string& buttonName);
	bool isClicked(int buttonID);

	void draw();

	bool isLoadedGuiPack(const std::string& guiPack);

	void createButton(const std::string& buttonName);
	void createButton(const std::string& buttonName, int layer);
	void createButton(const std::string& copyName, const std::string& originalName);

	void createAlias(const std::string& alias, const std::string& buttonName);

	void createButtonTemplate(const std::string& buttonName);
	void createButtonTemplate(const std::string& buttonName, int layer);
	void createButtonTemplate(const std::string& copyName, const std::string& originalName);

	void createBtnAtr(const std::string& atrName, gui::BtnAtr buttonAtr);
	void createBtnAtr(const std::string& buttonName, const std::string& atrName, gui::BtnAtr buttonAtr);
	void createBtnAtr(int buttonID, const std::string& atrName, gui::BtnAtr buttonAtr);

	void setButtonLayer(int layer);
	void setButtonLayer(const std::string& buttonName, int layer);
	void setButtonLayer(int buttonID, int layer);

	void createGroup(const std::string& groupName);
	void createGroupTemplate(const std::string& groupName);
	void createGroupFromTemplate(const std::string& groupName, const std::string& templateName);

	void addToGroup(const std::string& entryName);
	void addToGroup(const std::string& groupName, const std::string& entryName);

	[[deprecated]] std::string getGroupEntry(const std::string& groupName, const std::string& buttonName);
	int getGroupEntryID(const std::string& groupName, const std::string& buttonName);

	void createList(const std::string& listName);

	void setListTemplate(const std::string& groupTemplate);
	void setListTemplate(const std::string& listName, const std::string& groupTemplate);

	void setListSpacing(int spacing_x, int spacing_y);
	void setListSpacing(const std::string& listName, int spacing_x, int spacing_y);

	void setListPosition(std::pair<int, int> position);
	void setListPosition(const std::string& listName, std::pair<int, int> position);

	std::string createListEntry();
	std::string createListEntry(const std::string& listName);

	template <class T> void setButton(gui::BtnChar buttonChar, T value);
	template <class T> void setButton(int buttonID, gui::BtnChar buttonChar, T value);
	template <class T> void setButton(const std::string& buttonName, gui::BtnChar buttonChar, T value);

	template <class T> void setBtnAtr(gui::BtnAtrChar atrChar, T value);
	template <class T> void setBtnAtr(int buttonID, const std::string& atrName, gui::BtnAtrChar atrChar, T value);
	template <class T> void setBtnAtr(const std::string& buttonName, const std::string& atrName, gui::BtnAtrChar atrChar, T value);

	template <class T> void setGroupAtr(gui::BtnChar buttonChar, T value);
	template <class T> void setGroupAtr(const std::string& groupName, gui::BtnChar buttonChar, T value);

	template <class T> void setListAtr(gui::BtnChar buttonChar, T value);
	template <class T> void setListAtr(const std::string& listName, gui::BtnChar buttonChar, T value);

	void purgeButtons();
	void deleteList(const std::string& listName);
	void deleteGroup(const std::string& groupName);
	void deleteButton(const std::string& buttonName);
	void deleteButton(int buttonID);

	void setFont(sf::Font buttonFont);
	sf::Font* getFont() {return &buttonFont;}

	void setLang(std::string lang)
	{
		this->lang = lang;
		SaveFile langSave("Data/Language Pack/" + lang + "/gui.txt", true);
		if(langSave.readFile('='))
		{
			langPairs = langSave.getSaveList_uni();
		}
	}
	//TODO Have different context's for different categories, aka gui, items..
	std::u32string getText(const std::string& key)
	{
		std::u32string str = utl::toU32(key);
		for(auto& p : langPairs)
		{
			if(p.first == str)
			{
				return p.second;
			}
		}
		return U"nil";
	}
private:
	struct ListData
	{
		ListData(std::string name):listName(name) {}
		std::string listName;
		std::string groupTemplate = std::string();
		std::pair<int, int> position = std::make_pair(0,0);
		std::pair<int, int> listSpacing = std::make_pair(0,0);
		std::vector<std::string> groups;
	};

	//generates a button ID, saved pair as a hash in buttonIDs
	int getNewID(const std::string& buttonName);
	//creates a button, returns a reference to the button
	Button& emplaceButton(bool isTemplate, const std::string& buttonName, int templateID = -1);
	//copies the given button to a new one, returns a reference to the button
	Button& copyButton(Button& old, const std::string& buttonName, int templateID = -1);
	//returns the position in the buttons vector with the given ID, or -1 if it does not exist
	int getPos(const int buttonID);
	//returns the position in the buttons vector with the given name, or -1 if it does not exist
	int getPos(const std::string& name);

	//to see if a group entry exists
	bool groupExists(const std::string& entry);
#ifdef DEBUGMODE
	//to see if a group template entry exists
	bool groupTemplateExists(const std::string& entry);
#endif
	//to see if a list entry exists
	bool listExists(const std::string& list);
	//get the ID's that belong to the group entry
	std::vector<int>& getGroupIDs(const std::string& entry);
	//get the ListData given a listName
	ListData& getList(const std::string& listName);


	sf::RenderWindow& window;
	ResourceManager& resourceManager;

	utl::Vector2f mouseCoords;

	std::vector<Button> buttons;
	//all replacable button indecies
	std::vector<int> unusedPos;
	//holds all groups and group template compositions
	std::vector<std::pair<std::string, std::vector<int> > > groups;
#ifdef DEBUGMODE
	//holds names of all group templates, only for debugging
	std::vector<std::string> groupTemplates;
#endif
	std::vector<ListData> lists;
	//holds pointers to all drawable buttons, sorted by layer
	std::vector <Button*> visibleButtons;
	//holds drawing order of buttons, by buttonID
	std::vector<int> visibleButtonIDs;
	//keeps track off all loaded Gui Packs (only to be used by GuiLoader)
	std::vector<std::string> loadedGuiPacks;

	//hashes a button name to a buttonID
	std::unordered_map<std::string, int> buttonIDs;

	//button ID's are sequentially given, starting from 0
	int buttonCount = 0;

	//the most recently addressed element
	int lastButton = -1;
	std::string lastBtnAtr;
	std::string lastGroup;
	std::string lastList;

	//used only once per visible button
	void placeInDrawList(Button* button);
	//only to be used when button storage is modified
	void refreshDrawVector();

	sf::Font buttonFont;
	std::string lang;
	std::vector<std::pair<std::u32string, std::u32string>> langPairs;
};


///Templates
template <class T>
void GuiManager::setButton(gui::BtnChar buttonChar, T value)
{
	setButton(lastButton, buttonChar, value);
}
template <class T>
void GuiManager::setButton(int buttonID, gui::BtnChar buttonChar, T value)
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
void GuiManager::setButton(const std::string& buttonName, gui::BtnChar buttonChar, T value)
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
void GuiManager::setBtnAtr(gui::BtnAtrChar atrChar, T value)
{
	setBtnAtr(lastButton, lastBtnAtr, atrChar, value);
}
template <class T>
void GuiManager::setBtnAtr(int buttonID, const std::string& atrName, gui::BtnAtrChar atrChar, T value)
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
void GuiManager::setBtnAtr(const std::string& buttonName, const std::string& atrName, gui::BtnAtrChar atrChar, T value)
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
void GuiManager::setGroupAtr(gui::BtnChar buttonChar, T value)
{
	setGroupAtr(lastGroup, buttonChar, value);
}
template <class T>
void GuiManager::setGroupAtr(const std::string& groupName, gui::BtnChar buttonChar, T value)
{
#ifdef DEBUGMODE
	if(!groupExists(groupName))
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
void GuiManager::setListAtr(gui::BtnChar buttonChar, T value)
{
	setListAtr(lastList, buttonChar, value);
}
template <class T>
void GuiManager::setListAtr(const std::string& listName, gui::BtnChar buttonChar, T value)
{
#ifdef DEBUGMODE
	if(!listExists(listName))
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

///Inlines
inline int GuiManager::getNewID(const std::string& buttonName)
{
	int newButtonID = buttonCount;
	buttonCount++;
	buttonIDs.emplace(std::make_pair(buttonName, newButtonID));
	return newButtonID;
}
inline Button& GuiManager::emplaceButton(bool isTemplate, const std::string& buttonName, int templateID)
{
	int buttonID = getNewID(buttonName);
	if(unusedPos.size())
	{
		int pos = unusedPos.back();
		unusedPos.pop_back();
		buttons.at(pos) = Button(window, resourceManager, buttonFont, isTemplate, buttonID, templateID);
		return buttons.at(pos);
	}
	buttons.emplace_back(Button(window, resourceManager, buttonFont, isTemplate, buttonID, templateID));
	return buttons.back();
}
inline Button& GuiManager::copyButton(Button& old, const std::string& buttonName, int templateID)
{
	int buttonID = getNewID(buttonName);
	if(unusedPos.size())
	{
		int pos = unusedPos.back();
		unusedPos.pop_back();
		buttons.at(pos) = Button(old, buttonID, templateID);
		return buttons.at(pos);
	}
	buttons.emplace_back(Button(old, buttonID, templateID));
	return buttons.back();
}
inline int GuiManager::getPos(const int buttonID)
{
	for(unsigned int it = 0; it < buttons.size(); it++)
	{
		if(buttonID == buttons.at(it).buttonID)
		{
			return (int)it;
		}
	}
	return -1;
}
inline int GuiManager::getPos(const std::string& name)
{
#ifdef DEBUGMODE
	if(!buttonIDs.count(name))
	{
		return -1;
	}
#endif
	return(getPos(buttonIDs.at(name)));
}
inline bool GuiManager::groupExists(const std::string& entry)
{
	return (std::find_if(groups.begin(), groups.end(), [&](const std::pair<std::string, std::vector<int>>& s) {return s.first == entry;}) != groups.end());
}
#ifdef DEBUGMODE
inline bool GuiManager::groupTemplateExists(const std::string& entry)
{
	return (std::find_if(groupTemplates.begin(), groupTemplates.end(), [&](const std::string& s) {return s == entry;}) != groupTemplates.end());
}
#endif
inline bool GuiManager::listExists(const std::string& list)
{
	return (std::find_if(lists.begin(), lists.end(), [&](const ListData& l) {return l.listName == list;}) != lists.end());
}
inline std::vector<int>& GuiManager::getGroupIDs(const std::string& entry)
{
#ifdef DEBUGMODE
	if(!groupExists(entry))
	{
		LOG("Group with name: '" + entry + "' does not exist");
		return groups.back().second;
	}
#endif
	for(auto& it : groups)
	{
		if(it.first == entry)
		{
			return it.second;
		}
	}
	//should never reach here
	return groups.back().second;
}
inline GuiManager::ListData& GuiManager::getList(const std::string& listName)
{
#ifdef DEBUGMODE
	if(!listExists(listName))
	{
		LOG("List with name: '" + listName + "' does not exist");
		return lists.back();
	}
#endif
	for(auto& it : lists)
	{
		if(it.listName == listName)
		{
			return it;
		}
	}
	//should never reach here
	return lists.back();
}

#endif // GUIMANAGER_H
