#ifndef BUTTON_H
#define BUTTON_H

#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Logger.h"

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"

namespace gui
{

enum BtnAtr
{
    Sprite,
    Percent,
    Hover,
    Text
};
enum class BtnChar
{
    coords,
    bounds,
    scroll_x, scroll_y,
    addToScroll_x, addToScroll_y,
    isVisible,
    isActive,
    isTemplate,
    coords_group
};
enum class BtnAtrChar
{
    sprite,
    texture,
    flip,
    coords,
    color,
    charSize,
    text,
    transparency,
    size,
    percentage,
    direction
};

};

class Button
{
public:
	Button(sf::RenderWindow& window, ResourceManager& resourceManager, sf::Font& buttonFont, bool isTemplate, int buttonID, int buttonGroupID = -1) noexcept;
	//copy ctor creates 'real' buttons from templates or other 'real' buttons (copy does not hold template-ness)
	Button(const Button& oldButton, int buttonID, int buttonGroupID = -1) noexcept;
	Button(Button&&) noexcept = default;
	Button& operator= (const Button& other) noexcept;
	Button& operator= (Button&&) noexcept = default;
	~Button() noexcept = default;

	void addBtnAtr(const std::string& atrName, gui::BtnAtr buttonAtr) noexcept;

	void setButton(gui::BtnChar buttonChar, const std::string& value) noexcept;
	void setButton(gui::BtnChar buttonChar, const char* value) noexcept;
	void setButton(gui::BtnChar buttonChar, bool value) noexcept;
	void setButton(gui::BtnChar buttonChar, int value) noexcept;
	void setButton(gui::BtnChar buttonChar, std::pair <int, int> value) noexcept;

	void setBtnAtr(const std::string& atrName, gui::BtnAtrChar atrChar, const std::string& value) noexcept;
	void setBtnAtr(const std::string& atrName, gui::BtnAtrChar atrChar, const std::u32string& value) noexcept;
	void setBtnAtr(const std::string& atrName, gui::BtnAtrChar atrChar, std::pair<int, int> value) noexcept;
	void setBtnAtr(const std::string& atrName, gui::BtnAtrChar atrChar, sf::Color color) noexcept;
	void setBtnAtr(const std::string& atrName, gui::BtnAtrChar atrChar, int value) noexcept;
	void setBtnAtr(const std::string& atrName, gui::BtnAtrChar atrChar, char value) noexcept;

	void update(std::pair <int, int> mouseCoords) noexcept;
	void draw() noexcept;
	
	bool count(gui::BtnAtr atr, const std::string& atrName) const noexcept;

	sf::RenderWindow& window;
	ResourceManager& resourceManager;
	sf::Font& buttonFont;
	
	std::pair <int, int> buttonPosition = std::make_pair(0,0);
	std::pair <int, int> buttonBounds;
	int buttonID;
	int buttonGroupID;
	int layer = 1;
	int scroll_x = 0;
	int scroll_y = 0;
	bool isTemplate;
	bool isVisible;
	bool isCoordsChanged = true;
	bool isActive = true;
	bool isHovered = false;

	//atrs
	struct RegularSprite
	{
		RegularSprite(std::string name) noexcept: atrName(name){}
		RegularSprite(const RegularSprite& old) noexcept{copy(this, &old);}
		RegularSprite(RegularSprite&&) noexcept = default;
		RegularSprite& operator= (const RegularSprite& rhs) noexcept {copy(this, &rhs); return *this;}
		RegularSprite& operator= (RegularSprite&&) noexcept = default;
		~RegularSprite() noexcept = default;
		
		void copy(RegularSprite* copy, const RegularSprite* orig) noexcept
		{
			copy->atrName = orig->atrName;
			copy->sprite = orig->sprite;
			copy->position = orig->position;
			copy->isChanged = orig->isChanged;
		}
		
		std::string atrName;
		sf::Sprite sprite;
		std::pair <int, int> position = std::make_pair(0,0);
		bool isChanged = true;
	};
	struct ButtonText
	{
		ButtonText(std::string name, sf::Font& font) noexcept: atrName(name)
		{
			text.setFont(font);
			text.setFillColor(sf::Color::Black); text.setOutlineColor(sf::Color::Black);
		}
		ButtonText(const ButtonText& old) noexcept {copy(this, &old);}
		ButtonText(ButtonText&&) noexcept = default;
		ButtonText& operator= (const ButtonText& rhs) noexcept {copy(this, &rhs); return *this;}
		ButtonText& operator= (ButtonText&&) noexcept = default;
		~ButtonText() noexcept = default;
		
		void copy(ButtonText* copy, const ButtonText* orig) noexcept
		{
			copy->atrName = orig->atrName;
			copy->text = orig->text;
			copy->position = orig->position;
			copy->isChanged = orig->isChanged;
		}
		
		std::string atrName;
		sf::Text text;
		std::pair <int, int> position = std::make_pair(0,0);
		bool isChanged = true;
	};
	struct OverlaySprite
	{
		OverlaySprite(std::string name, sf::Vector2f bounds) noexcept: atrName(name)
		{
			rectOverlay.setFillColor(sf::Color(0,0,0, 100));
			rectOverlay.setSize(bounds);
		}
		OverlaySprite(const OverlaySprite& old) noexcept {copy(this, &old);}
		OverlaySprite(OverlaySprite&&) noexcept = default;
		OverlaySprite& operator= (const OverlaySprite& rhs) noexcept {copy(this, &rhs); return *this;}
		OverlaySprite& operator= (OverlaySprite&&) noexcept = default;
		~OverlaySprite() noexcept = default;
		
		void copy(OverlaySprite* copy, const OverlaySprite* orig) noexcept
		{
			copy->atrName = orig->atrName;
			copy->rectOverlay = orig->rectOverlay;
			copy->position = orig->position;
			copy->isChanged = orig->isChanged;
		}
		
		std::string atrName;
		sf::RectangleShape rectOverlay;
		std::pair <int, int> position = std::make_pair(0,0);
		bool isChanged = true;
	};
	struct PercentSprite
	{
		PercentSprite(std::string name) noexcept: atrName(name){}
		PercentSprite(const PercentSprite& old) noexcept {copy(this, &old);}
		PercentSprite(PercentSprite&&) noexcept = default;
		PercentSprite& operator= (const PercentSprite& rhs) noexcept {copy(this, &rhs); return *this;}
		PercentSprite& operator= (PercentSprite&&) noexcept = default;
		~PercentSprite() noexcept = default;
		
		void copy(PercentSprite* copy, const PercentSprite* orig) noexcept
		{
			copy->atrName = orig->atrName;
			copy->sprite = orig->sprite;
			copy->rectOverlay = orig->rectOverlay;
			copy->spritePercentage = orig->spritePercentage;
			copy->directionOfGap = orig->directionOfGap;
			copy->originalTextureRect = orig->originalTextureRect;
			copy->position = orig->position;
			copy->isChanged = orig->isChanged;
		}
		
		std::string atrName;
		sf::Sprite sprite;
		sf::RectangleShape rectOverlay;
		float spritePercentage = 1.f;
		utl::Direction directionOfGap = utl::Direction::right;
		sf::IntRect originalTextureRect = sf::IntRect(0,0,0,0);
		std::pair <int, int> position = std::make_pair(0,0);
		bool isChanged = true;
	};

	std::vector<RegularSprite> sprites;
	std::vector<ButtonText> texts;
	std::vector<OverlaySprite> hovers;
	std::vector<PercentSprite> percents;

private:
	template<class T>
	inline int count(const std::string& name, const std::vector<T>& vec) const noexcept
	{
		for(unsigned int it = 0; it < vec.size(); it++)
		{
			if(name == vec.at(it).atrName)
			{
				return (int)it;
			}
		}
		return -1;
	}

};



#endif // BUTTON_H
