#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <algorithm>
#include <string>

#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"

#include "QuestiaEng/Utl/Type/Vector2.h"

class QueryWindow
{
public:
    QueryWindow(GuiManager& _guiManager, GuiLoader& _guiLoader);
    ~QueryWindow();

    enum class QueryType {Input_int, Input_string, Choice_string};

    void addQuery(std::string queryID, std::string queryQuestion, QueryType queryType);
    void initQuery(std::string windowName);

    void setActive(bool isActive);
    bool isActive();

    void resetQueries();

    int getResult_int(std::string queryID);
    std::string getResult_string(std::string queryID);
    std::string getChoice_string();

    void checkInput(bool isMouseClicked, char inputText);

    bool isDone();
    bool isWindow(std::string question);

private:
    GuiManager& guiManager;
    GuiLoader& guiLoader;

    bool isWindowActive = false;
    bool isWindowDone = false;
    bool scrollWindow = false;
    int scrollAmount = 0;

    struct Query
    {
        Query(std::string _queryQuestion, QueryType _queryType):queryQuestion(_queryQuestion), queryType(_queryType){}

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
