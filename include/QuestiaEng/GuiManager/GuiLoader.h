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

    void loadGui(GuiManager& guiManager, const std::string& gui);
    void setGuiPack(const std::string& guiPack);

private:
    std::string primaryPack = "Default";
    std::string secondaryPack = "Default";

    SaveFile guiFile;

    gui::BtnAtr getBtnAtr(std::string buttonAtr);
    gui::BtnAtrChar getBtnAtrChar(std::string buttonAtrCharacteristic);
    gui::BtnChar getBtnChar(std::string buttonCharacteristic);
};

#endif // GUILOADER_H
