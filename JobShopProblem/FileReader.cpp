#include "FileReader.hpp"
#include "Utilities.hpp"

#include <memory>
#include <fstream>

namespace Utilities
{
    std::shared_ptr<FileReader> FileReader::Instance()
    {
        if (nullptr == mInstance)
        {
            mInstance.reset(new FileReader);
        }

        return mInstance;
    }

    FileReader::FileReader()
    {

    }

    FileReader::~FileReader()
    {

    }

    bool FileReader::readData(const std::string fileName)
    {
        std::ifstream fileStream;

        try
        {
            fileStream.open(fileName, std::ifstream::in);
        }
        catch (...)
        {
            return false;
        }

        Utilities::readLines(fileStream, std::back_inserter(mReadData));

        return true;
    }

    const std::vector< std::string > & FileReader::getReadData() const
    {
        return mReadData;
    }

    std::shared_ptr<FileReader> FileReader::mInstance;
}