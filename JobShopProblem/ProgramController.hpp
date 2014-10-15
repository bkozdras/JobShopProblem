#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

class ProgramController
{
    public:

        typedef std::function<bool()> Task;
        enum class TaskName : unsigned int { ReadData, ParseData, InitializeJobShopData };
        typedef std::vector< TaskName > TaskList;

        static void initialize(std::initializer_list< TaskName > taskList);
        static bool run();

    private:

        static void initializeTaskMap();

        static bool readDataInputFile();
        static bool parseReadData();
        static bool initializeJobShopData();

        static void handleTaskError(const TaskName & taskName);

        static std::map<TaskName, Task> mTaskMap;
        static std::vector<TaskName> mTaskList;
};