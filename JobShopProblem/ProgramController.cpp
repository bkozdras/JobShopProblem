#include "ProgramController.hpp"
#include "JobShopData.hpp"
#include "FileReader.hpp"
#include "Data.hpp"
#include "Utilities.hpp"
#include <utility>
#include <functional>
#include <iostream>
#include <cassert>

void ProgramController::initialize(std::initializer_list< ProgramController::TaskName > taskList)
{
    initializeTaskMap();

    mTaskList.clear();
    mTaskList.insert(mTaskList.end(), taskList.begin(), taskList.end());
}

ProgramController::ExecuteResult ProgramController::run()
{
    ExecuteResult executeResult = ExecuteResult::Success;

    for (const auto & taskName : mTaskList)
    {
        auto & task = mTaskMap[taskName];
        ExecuteResult executeResult = task();
        if (ExecuteResult::Failure == executeResult)
        {
            handleTaskError(taskName);
            return executeResult;
        }
    }

    return executeResult;
}

void ProgramController::initializeTaskMap()
{
    if (mTaskMap.empty())
    {
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::ReadData, std::bind((ExecuteResult(*)())&ProgramController::readDataInputFile)));
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::ParseData, std::bind((ExecuteResult(*)())&ProgramController::parseReadData)));
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::InitializeJobShopData, std::bind((ExecuteResult(*)())&ProgramController::initializeJobShopData)));
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::CalculateJobShopTables, std::bind((ExecuteResult(*)())&ProgramController::calculateJobShopTables)));
    }
}

ProgramController::ExecuteResult ProgramController::readDataInputFile()
{
    const std::string fileName = Program::Details::DataFileName();

    bool readResult = Utilities::FileReader::Instance()->readData(fileName);

    return returnExecuteResult(readResult);
}

ProgramController::ExecuteResult ProgramController::parseReadData()
{
    std::vector< std::vector<int> > readIntLines;
    const std::vector< std::string > & readData = Utilities::FileReader::Instance()->getReadData();
    bool result = Utilities::StringParser::convert(readData, readIntLines);

    Types::NumberOfJobs numberOfJobs = readIntLines[0][0];
    Types::NumberOfMachines numberOfMachines = readIntLines[0][1];

    Program::Details::JobShopData().setNumberOfJobs(numberOfJobs);
    Program::Details::JobShopData().setNumberOfMachines(numberOfMachines);

    Program::Details::ReadDataFromFile(std::move(readIntLines));

    return returnExecuteResult(result);
}

ProgramController::ExecuteResult ProgramController::initializeJobShopData()
{
    Program::Details::JobShopData().initializeT();
    Program::Details::JobShopData().initializeA();
    Program::Details::JobShopData().initializeP();
    Program::Details::JobShopData().initializeC();
    Program::Details::JobShopData().initializeS();
    Program::Details::JobShopData().initializePh();
    Program::Details::JobShopData().initializeCriticalPath();

    return returnExecuteResult(true);
}

ProgramController::ExecuteResult ProgramController::calculateJobShopTables()
{
    //alg. wstepny
    Program::Details::JobShopData().fillLO();
    Program::Details::JobShopData().fillOFs();
    Program::Details::JobShopData().fillPI();
    Program::Details::JobShopData().fillPS();
    Program::Details::JobShopData().fillLP();
    Program::Details::JobShopData().prepareQueue();
    Program::Details::JobShopData().countCmax();
    Program::Details::JobShopData().fillPH();
    Program::Details::JobShopData().fillCriticalPath();
    Program::Details::JobShopData().fillPH2();
    //alg. zstepujacy
    Program::Details::JobShopData().AlgorytmZstepujacy();



    return returnExecuteResult(true);
}

void ProgramController::handleTaskError(const ProgramController::TaskName & taskName)
{
    switch (taskName)
    {
        case TaskName::ReadData:
        {
            std::cout << "Handle task error: Fail during reading data from provided file!" << std::endl;
            break;
        }

        case TaskName::ParseData:
        {
            std::cout << "Handle task error: Fail during parsing read data!" << std::endl;
            break;
        }

        case TaskName::InitializeJobShopData:
        {
            std::cout << "Handle task error: Fail during initializing job shop data!" << std::endl;
            break;
        }

        default:
        {
            assert(0 && "ProgramController::handleTaskError: Add missed value to switch statement");
        }
    }
}

ProgramController::ExecuteResult ProgramController::returnExecuteResult(bool result)
{
    if (result)
    {
        return ExecuteResult::Success;
    }
    else
    {
        return ExecuteResult::Failure;
    }
}

std::string ProgramController::getEnumString(const ProgramController::ExecuteResult & executeResult)
{
    switch (executeResult)
    {
        case ExecuteResult::Failure :
        {
            return "ExecuteResult_Failure";
        }

        case ExecuteResult::Success :
        {
            return "ExecuteResult_Success";
        }

        default:
        {
            assert(0 && "ProgramController::getEnumString: Add missed value to switch statement");
        }
    }

    return "";
}

std::ostream & operator<< (std::ostream & stream, const ProgramController::ExecuteResult & executeResult)
{
    return ( stream << ProgramController::getEnumString(executeResult) ); 
}

std::map<ProgramController::TaskName, ProgramController::Task> ProgramController::mTaskMap;
std::vector<ProgramController::TaskName> ProgramController::mTaskList;