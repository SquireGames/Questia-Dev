#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <algorithm>

#include <iostream>

#include "QuestiaEng/Utl/Ticker.h"

namespace utl
{

class Executor
{
public:
    Executor();
    ~Executor();

    enum class TaskType {Continuous, Delayed};

    void addTask(const std::string& taskName, TaskType taskType, utl::Ticker ticker, std::function<void(float taskPercentage)> task);
    void processTasks();

    void tryDelete(const std::string& taskName);

private:
    struct Event
    {
        Event(TaskType _taskType, utl::Ticker _ticker, std::function<void(float taskPercentage)> _task):
            taskType(_taskType)
            , ticker(_ticker)
            , task(_task)
        {}
        TaskType taskType;
        utl::Ticker ticker;
        std::function<void(float taskPercentage)> task;
    };

    std::vector<std::pair<std::string, std::unique_ptr<Event>>> eventVector;
};

}

#endif // EXECUTOR_H
