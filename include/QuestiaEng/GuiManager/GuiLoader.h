#ifndef GUILOADER_H
#define GUILOADER_H

#include "QuestiaEng/Utl/SaveFile.h"
#include "QuestiaEng/GuiManager/GuiManager.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/FileData.h"

class GuiLoader
{
public:
    GuiLoader();
    ~GuiLoader();

    void loadGui(GuiManager& guiManager, std::string gui);
    void setGuiPack(std::string guiPack);

private:
    std::string primaryPack = "Default";
    std::string secondaryPack = "Default";

    SaveFile guiFile;

    gui::ButtonAtr getButtonAtr(std::string buttonAtr);
    gui::ButtonAtrCharacteristic getButtonAtrCharacteristic(std::string buttonAtrCharacteristic);
    gui::ButtonCharacteristic getButtonCharacteristic(std::string buttonCharacteristic);
};

#endif // GUILOADER_H
