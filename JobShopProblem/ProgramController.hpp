#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <ostream>

class ProgramController
{
    public:

        enum class ExecuteResult : unsigned int { Success, Failure };
        friend std::ostream & operator<< (std::ostream & stream, const ExecuteResult & executeResult);

        typedef std::function<ExecuteResult()> Task;
        enum class TaskName : unsigned int { ReadData, ParseData, InitializeJobShopData };
        typedef std::vector< TaskName > TaskList;

        static void initialize(std::initializer_list< TaskName > taskList);
        static ExecuteResult run();

    private:

        static void initializeTaskMap();

        static ExecuteResult readDataInputFile();
        static ExecuteResult parseReadData();
        static ExecuteResult initializeJobShopData();

        static void handleTaskError(const TaskName & taskName);
        static ExecuteResult returnExecuteResult(bool result);

        static std::string getEnumString(const ExecuteResult & executeResult);

        static std::map<TaskName, Task> mTaskMap;
        static std::vector<TaskName> mTaskList;
};