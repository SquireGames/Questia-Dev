#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>


#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/GuiManager/Button.h"

#include "QuestiaEng/Utl/Type/Vector2.h"


class GuiManager
{
public:
    GuiManager(sf::RenderWindow &_window, ResourceManager &_resourceManager);
    ~GuiManager();

    void createButton(std::string buttonName);
    void createButton(std::string buttonName, int layer);
    void createButton(std::string copyName, std::string originalName);
	void createAlias(std::string alias, std::string buttonName);
    void createButtonTemplate(std::string buttonName);
    void createButtonTemplate(std::string buttonName, int layer);
    void createButtonTemplate(std::string copyName, std::string originalName);
    void createBtnAtr(std::string atrName, gui::BtnAtr buttonAtr);
    void createBtnAtr(std::string buttonName, std::string atrName, gui::BtnAtr buttonAtr);
    void setButtonLayer(std::string buttonName, int layer);
    void setButtonLayer(int layer);

    void createGroup(std::string groupName);
    void createGroupTemplate(std::string groupName);
    void createGroupFromTemplate(std::string groupName, std::string templateName);
    void addToGroup (std::string groupName, std::string entryName);
    void addToGroup (std::string entryName);
    std::string getGroupEntry(std::string groupName, std::string buttonName);

    void createList(std::string listName);
    void setListSpacing(std::string listName, int spacing_x, int spacing_y);
    void setListSpacing(int spacing_x, int spacing_y);
    void setListTemplate(std::string listName, std::string groupTemplate);
    void setListTemplate(std::string groupTemplate);
    void setListPosition(std::string listName, std::pair<int, int> position);
    void setListPosition(std::pair<int, int> position);
    std::string createListEntry(std::string listName);
    std::string createListEntry();

    bool isClicked(std::string buttonName);
    void draw();
	
    void deleteButton(std::string buttonName);
    void deleteGroup(std::string groupName);
    void deleteList(std::string listName);
	void purgeButtons();
	
    void setMousePosition(utl::Vector2f _mouseCoords);
    bool isLoadedGuiPack(std::string guiPack);
    void setFont(sf::Font _buttonFont);
	sf::Font* getFont() {return &buttonFont;}

    template <class T>
    void setButton(std::string buttonName, gui::BtnChar buttonChar, T value)
    {
        buttonMap[buttonName]->setButton(buttonChar, value);
    }
    template <class T>
    void setButton(gui::BtnChar buttonChar, T value)
    {
        buttonMap[currentButtonEdit]->setButton(buttonChar, value);
    }
    template <class T>
    void setBtnAtr(std::string buttonName, std::string atrName, gui::BtnAtrChar atrChar, T value)
    {
        buttonMap[buttonName]->setBtnAtr(atrName, atrChar, value);
    }
    template <class T>
    void setBtnAtr(gui::BtnAtrChar atrChar, T value)
    {
        buttonMap[currentButtonEdit]->setBtnAtr(currentBtnAtrEdit, atrChar, value);
    }

    template <class T>
    void setGroupAtr(std::string groupName, gui::BtnChar buttonChar, T value)
    {
        if(buttonChar == gui::BtnChar::coords)
        {
            buttonChar = gui::BtnChar::coords_group;
        }
        if(groupMap.count(groupName))
        {
            const std::vector <std::string>& buttonVec = groupMap[groupName];
            for(unsigned int it = 0; it != buttonVec.size(); it++)
            {
                buttonMap[buttonVec[it]]->setButton(buttonChar, value);
            }
        }
    }
    template <class T>
    void setGroupAtr(gui::BtnChar buttonChar, T value)
    {
        if(buttonChar == gui::BtnChar::coords)
        {
            buttonChar = gui::BtnChar::coords_group;
        }
        if(groupMap.count(currentGroupEdit))
        {
            const std::vector <std::string>& buttonVec = groupMap[currentGroupEdit];
            for(unsigned int it = 0; it != buttonVec.size(); it++)
            {
                buttonMap[buttonVec[it]]->setButton(buttonChar, value);
            }
        }
    }
    template <class T>
    void setListAtr(std::string listName, gui::BtnChar buttonChar, T value)
    {
        for(const std::string& groupIt : listMap[listName].elementGroups)
        {
            setGroupAtr(groupIt, buttonChar, value);
        }
    }
    template <class T>
    void setListAtr(gui::BtnChar buttonChar, T value)
    {
        for(const std::string& groupIt : listMap[currentListEdit].elementGroups)
        {
            setGroupAtr(groupIt, buttonChar, value);
        }
    }

private:
    sf::RenderWindow& window;
    ResourceManager &resourceManager;

    std::string currentButtonEdit;
    std::string currentBtnAtrEdit;
    std::string currentGroupEdit;
    std::string currentListEdit;

    utl::Vector2f mouseCoords;

    std::map <std::string, Button*> buttonMap;
	std::map <std::string, std::string> aliasMap;
    std::list <Button*> buttonDrawList;
    void placeInDrawList(Button* button);

    std::map <std::string, std::vector <std::string> > groupMap;
    std::map <std::string, std::vector <std::string> > groupTemplateMap;

	struct ListData
	{
		std::string groupTemplate = "NOTEMPLATE";
		std::pair<int, int> position = std::make_pair(0,0);
		std::pair<int, int> listSpacing = std::make_pair(0,0);
		std::vector<std::string> elementGroups;
	};

    std::map <std::string, ListData> listMap;

    std::vector<std::string> loadedGuiPacks;

    sf::Font buttonFont;
    int buttonCount = 0;
};


#endif // GUIMANAGER_H
