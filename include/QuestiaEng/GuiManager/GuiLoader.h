#ifndef GUILOADER_H
#define GUILOADER_H

#include "QuestiaEng/GuiManager/Button.h"
#include "QuestiaEng/Utl/SaveFile.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/FileData.h"

class GuiManager;

class GuiLoader
{
public:
	GuiLoader(GuiManager& guiManager) noexcept;
	GuiLoader(GuiLoader&&) noexcept = default;
	GuiLoader& operator= (GuiLoader&&) noexcept = default;
	~GuiLoader() noexcept = default;

	GuiLoader(const GuiLoader&) = delete;
	GuiLoader& operator= (const GuiLoader&) = delete;

	void loadGui(const std::string& gui) noexcept;
	void setGuiPack(const std::string& gui) noexcept;

private:
	bool isLoadedGui(const std::string& gui) const noexcept;
	gui::BtnAtr getBtnAtr(const std::string& buttonAtr) const noexcept;
	gui::BtnAtrChar getBtnAtrChar(const std::string& buttonAtrCharacteristic) const noexcept;
	gui::BtnChar getBtnChar(const std::string& buttonCharacteristic) const noexcept;

	GuiManager& guiManager;

	std::string primaryPack = "Default";
	std::string secondaryPack = "Default";
	std::vector<std::string> loadedGuis;

	SaveFile guiFile;

	friend class GuiBuilder;
};

#endif // GUILOADER_H
