#ifndef OPTIONMANAGER_H
#define OPTIONMANAGER_H

#include <vector>

#include "QuestiaEng/StateManager/States/State_OptionsMenu/Option.h"
#include "QuestiaEng/StateManager/States/State_OptionsMenu/Option_Base.h"

#include "QuestiaEng/Utl/SaveFile/SaveFile_Options.h"

#include "QuestiaEng/GuiManager/GuiManager.h"

#include "QuestiaEng/Utl/Controls/Keyboard.h"

struct ButtonData
{
    std::string buttonName = "nil";
    bool isActive = false;
};

struct OptionData
{
    ButtonData leftButton;
    ButtonData rightButton;
    ButtonData functionButton;

    std::string textButtonName = "nil";
    std::string* displayString = nullptr;
};

class OptionManager
{
public:
    //ctor and dtor
    OptionManager(GuiManager* _guiManager);
    ~OptionManager();

    void addOption(Option_Base* option);
    void initLists();

    void saveOptions(SaveFile_Options& saveFile);

    bool handleGui();
    void handleInput(ctr::Input input);

    void setMouseReleased();
    void checkMouseInput();

    bool isMouseOverAssignedInput();

private:
    GuiManager* guiManager;

    void initSprites();
    void updateArrows();
    std::string assignInput = "nil";

    std::vector <std::pair <Option_Base*, OptionData> > optionVector;

    bool mouseReleases = 0;
};

#endif // OPTIONMANAGER_H
