#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <algorithm>
#include <string>
#include <functional>

#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiElement/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"

#include "QuestiaEng/Utl/Type/Vector2.h"

class QueryWindow : public GuiElement
{
public:
	QueryWindow();
	~QueryWindow();

	enum class QueryType {Input_int, Input_string, Choice_string};

	void addQuery(const std::string& queryID, const std::string& queryQuestion, QueryType queryType);
	void init(const std::string& windowName, GuiManager& pGuiManager, GuiLoader* guiLoader, std::function<void()> handle);
	void reInit();

	void setActive(bool isActive);
	bool isActive();

	void resetQueries();

	int getResult_int(const std::string& queryID);
	std::string getResult_string(const std::string& queryID);
	std::string getChoice_string();

	//GuiElement
	void handleInput(std::u32string& input);
	void update(MouseListener& mouse);

	bool isDone();
	bool isWindow(const std::string& question);

private:
	GuiManager* guiManager;

	std::function<void()> handleRes;

	bool isWindowActive = false;
	bool isWindowDone = false;
	bool scrollWindow = false;
	int scrollAmount = 0;

	struct Query
	{
		Query(std::string queryQuestion, QueryType queryType):queryQuestion(queryQuestion), queryType(queryType) {}

		std::string buttonName;

		std::string queryQuestion;
		QueryType queryType;
		std::string queryAnswer;
	};

	int windowSize_x = 700;
	int windowSize_y = 100;
	int windowPos_x =  610;
	int windowPos_y =  500;

	int querySelection = -1;

	std::string groupName;
	std::string button_windowBox;
	std::string button_closeButton;
	std::string button_submitButton;

	std::vector<std::pair<std::string, Query>> queryValues;
};

#endif // QUERYWINDOW_H
