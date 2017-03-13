#ifndef OPTION_BASE_H
#define OPTION_BASE_H

#include <string>
#include "QuestiaEng/Utl/Controls/Keyboard.h"

enum class OptionType {choice, functional, input};

//for container iteration through options

class Option_Base
{
public:
    Option_Base();
    virtual ~Option_Base();

    virtual std::string getValueString() = 0;

    virtual OptionType getType() = 0;
    virtual void setInput(ctr::Input input) = 0;

    virtual bool isChanged() = 0;

    virtual std::string getList() = 0;
    virtual void setList(std::string) = 0;

    virtual void iterateForward() = 0;
    virtual void iterateBackward() = 0;
    virtual void callFunction() = 0;

    virtual bool isEnd() = 0;
    virtual bool isBegin() = 0;

    virtual std::string* getDisplayString() = 0;
    virtual std::string getOptionName() = 0;
};

#endif // OPTION_BASE_H
