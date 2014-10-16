#include "Data.hpp"
#include "JobShopData.hpp"

namespace Program
{
    void Details::DataFileName(const std::string & dataFileName)
    {
        mDataFileName = dataFileName;
    }

    void Details::DataFileName(std::string && dataFileName)
    {
        mDataFileName = std::move(dataFileName);
    }

    std::string & Details::DataFileName()
    {
        return mDataFileName;
    }

    void Details::ReadDataFromFile(std::vector< std::vector< int > > && readDataFromFile)
    {
        mReadDataFromFile = std::move(readDataFromFile);
    }

    Types::JobShopData & Details::JobShopData()
    {
        return mJobShopData;
    }

    const std::vector< std::vector< int > > & Details::ReadDataFromFile()
    {
        return Details::mReadDataFromFile;
    }

    std::string Details::mDataFileName;
    Types::JobShopData Details::mJobShopData;
    std::vector< std::vector< int > > Details::mReadDataFromFile;
}