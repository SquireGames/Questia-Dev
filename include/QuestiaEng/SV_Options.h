#ifndef SV_OPTIONS_H
#define SV_OPTIONS_H

#include <string>

#include "QuestiaEng/Utl/SaveFile.h"
#include "QuestiaEng/Utl/FileData.h"
#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Controls/Input.h"

class SV_Options
{
public:
    SV_Options();
    ~SV_Options();

    void saveOption(const std::string& optionName, const std::string& valueStr);
    void writeOptions();

    void reloadOptions();

    int getWindowMode();
    int getFps();	
    std::string getFont();
	std::string getGuiPack();	
    int getMusicVolume();	
	std::string getLang();
    ctr::Input getKey_moveUp();		
    ctr::Input getKey_moveDown();	
    ctr::Input getKey_moveLeft();	
    ctr::Input getKey_moveRight();	
    ctr::Input getKey_skill_1();	
    ctr::Input getKey_skill_2();	
    ctr::Input getKey_skill_3();	
    ctr::Input getKey_skill_4();	
    ctr::Input getKey_skill_5();	
    ctr::Input getKey_skill_6();

    std::string getWindowMode_name();
    std::string getFps_name();
    std::string getFont_name();
	std::string getGuiPack_name();
	std::string getLang_name();
    std::string getMusicVolume_name();
    std::string getKey_moveUp_name();
    std::string getKey_moveDown_name();
    std::string getKey_moveLeft_name();
    std::string getKey_moveRight_name();
    std::string getKey_skill_1_name();
    std::string getKey_skill_2_name();
    std::string getKey_skill_3_name();
    std::string getKey_skill_4_name();
    std::string getKey_skill_5_name();
    std::string getKey_skill_6_name();

private:
    ///save
    SaveFile saveFile;

    ///options
    //windowMode: 0 = full-screen, 1+ = 1080p windowed
    int windowMode = 0;
    //fps: -1 = Unlimited, 0 = V-Sync, 1+ = x fps
    int fps = 0;
    //font: x = font file name
    std::string font = "Lato-Regular.ttf";
    //guiPack: x = guiPack folder name
    std::string guiPack = "Default";
	//lang: x = lang folder dir name
	std::string language = "en";

    //musicVolume: x = volume out of 100
    int musicVolume = 0;

    //key_x: x = key saved as int
    ctr::Input key_moveUp    = ctr::Input::W;
    ctr::Input key_moveDown  = ctr::Input::S;
    ctr::Input key_moveLeft  = ctr::Input::A;
    ctr::Input key_moveRight = ctr::Input::D;
    ctr::Input key_skill_1   = ctr::Input::LMouse;
    ctr::Input key_skill_2   = ctr::Input::RMouse;
    ctr::Input key_skill_3   = ctr::Input::LShift;
    ctr::Input key_skill_4   = ctr::Input::Space;
    ctr::Input key_skill_5   = ctr::Input::Q;
    ctr::Input key_skill_6   = ctr::Input::E;

    ///option names
    const std::string windowMode_name  = "Window Setting";
    const std::string fps_name         = "Frames Per Second";
    const std::string font_name        = "Font";
    const std::string guiPack_name     = "Gui Pack";
    const std::string language_name    = "Language";
    const std::string musicVolume_name = "Music Volume";

    //key bindings
    const std::string key_moveUp_name    = "Move Up";
    const std::string key_moveDown_name  = "Move Down";
    const std::string key_moveLeft_name  = "Move Left";
    const std::string key_moveRight_name = "Move Right";
    const std::string key_skill_1_name = "Skill 1";
    const std::string key_skill_2_name = "Skill 2";
    const std::string key_skill_3_name = "Skill 3";
    const std::string key_skill_4_name = "Skill 4";
    const std::string key_skill_5_name = "Skill 5";
    const std::string key_skill_6_name = "Skill 6";
};

#endif // SV_OPTIONS_H
