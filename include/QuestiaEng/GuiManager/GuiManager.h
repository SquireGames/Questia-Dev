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
    void createButtonTemplate(std::string buttonName);
    void createButtonTemplate(std::string buttonName, int layer);
    void createButtonTemplate(std::string copyName, std::string originalName);
    void createButtonAtr(std::string atrName, gui::ButtonAtr buttonAtr);
    void createButtonAtr(std::string buttonName, std::string atrName, gui::ButtonAtr buttonAtr);
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
    void drawButtons();
    void deleteButton(std::string buttonName);
	void purgeButtons();
    void setMousePosition(utl::Vector2f _mouseCoords);
    void setFont(sf::Font _buttonFont);

    template <class T>
    void setButton(std::string buttonName, gui::ButtonCharacteristic buttonChar, T value)
    {
        buttonMap[buttonName]->setButton(buttonChar, value);
    }
    template <class T>
    void setButton(gui::ButtonCharacteristic buttonChar, T value)
    {
        buttonMap[currentButtonEdit]->setButton(buttonChar, value);
    }
    template <class T>
    void setButtonAtr(std::string buttonName, std::string atrName, gui::ButtonAtrCharacteristic atrChar, T value)
    {
        buttonMap[buttonName]->setButtonAtr(atrName, atrChar, value);
    }
    template <class T>
    void setButtonAtr(gui::ButtonAtrCharacteristic atrChar, T value)
    {
        buttonMap[currentButtonEdit]->setButtonAtr(currentButtonAtrEdit, atrChar, value);
    }


    template <class T>
    void setGroupAtr(std::string groupName, gui::ButtonCharacteristic buttonChar, T value)
    {
        if(buttonChar == gui::ButtonCharacteristic::coords)
        {
            buttonChar = gui::ButtonCharacteristic::coords_group;
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
    void setGroupAtr(gui::ButtonCharacteristic buttonChar, T value)
    {
        if(buttonChar == gui::ButtonCharacteristic::coords)
        {
            buttonChar = gui::ButtonCharacteristic::coords_group;
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
    void setListAtr(std::string listName, gui::ButtonCharacteristic buttonChar, T value)
    {
        for(const std::string& groupIt : listMap[listName].second)
        {
            setGroupAtr(groupIt, buttonChar, value);
        }
    }
    template <class T>
    void setListAtr(gui::ButtonCharacteristic buttonChar, T value)
    {
        for(const std::string& groupIt : listMap[currentListEdit].second)
        {
            setGroupAtr(groupIt, buttonChar, value);
        }
    }

    bool isLoadedGuiPack(std::string guiPack)
    {
        if(std::find(loadedGuiPacks.begin(), loadedGuiPacks.end(), guiPack) == loadedGuiPacks.end())
        {
            std::cout << "GUIMANAGER: Attempting to load GuiPack - " << guiPack << std::endl;
            loadedGuiPacks.push_back(guiPack);
            return false;
        }
        return true;
    }

private:
    sf::RenderWindow& window;
    ResourceManager &resourceManager;

    std::string currentButtonEdit;
    std::string currentButtonAtrEdit;
    std::string currentGroupEdit;
    std::string currentListEdit;

    utl::Vector2f mouseCoords;

    std::map <std::string, Button*> buttonMap;
    std::list <Button*> buttonDrawList;
    void placeInDrawList(Button* button);

    std::map <std::string, std::vector <std::string> > groupMap;
    std::map <std::string, std::vector <std::string> > groupTemplateMap;

    std::map <std::string, std::pair <std::pair <std::string, std::pair <std::pair <int, int>, std::pair<int, int>>>,std::vector <std::string > > > listMap;

    std::vector<std::string> loadedGuiPacks;

    sf::Font buttonFont;
    int buttonCount = 0;
};


#endif // GUIMANAGER_H
