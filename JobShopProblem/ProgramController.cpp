#include "ProgramController.hpp"
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

bool ProgramController::run()
{
    for (const auto & taskName : mTaskList)
    {
        auto & task = mTaskMap[taskName];
        bool result = task();
        if (false == result)
        {
            handleTaskError(taskName);
            return false;
        }
    }

    return true;
}

void ProgramController::initializeTaskMap()
{
    if (mTaskMap.empty())
    {
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::ReadData, std::bind((bool(*)())&ProgramController::readDataInputFile)));
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::ParseData, std::bind((bool(*)())&ProgramController::parseReadData)));
        mTaskMap.insert(std::pair<TaskName, Task>(TaskName::InitializeJobShopData, std::bind((bool(*)())&ProgramController::initializeJobShopData)));
    }
}

bool ProgramController::readDataInputFile()
{
    const std::string fileName = Program::Details::DataFileName();
    return Utilities::FileReader::Instance()->readData(fileName);
}

bool ProgramController::parseReadData()
{
    std::vector< std::vector< int > > readIntLines;
    const std::vector< std::string > & readData = Utilities::FileReader::Instance()->getReadData();
    bool result = Utilities::StringParser::convert(readData, readIntLines);

    Types::NumberOfJobs numberOfJobs = readIntLines[0][0];
    Types::NumberOfMachines numberOfMachines = readIntLines[0][1];

    Program::Details::JobShopData().setNumberOfJobs(numberOfJobs);
    Program::Details::JobShopData().setNumberOfMachines(numberOfMachines);

    Program::Details::ReadDataFromFile(std::move(readIntLines));

    return result;
}

bool ProgramController::initializeJobShopData()
{
    Program::Details::JobShopData().initializeT();

    return true;
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

std::map<ProgramController::TaskName, ProgramController::Task> ProgramController::mTaskMap;
std::vector<ProgramController::TaskName> ProgramController::mTaskList;