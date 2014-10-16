#include "Data.hpp"

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

    std::string Details::mDataFileName;
    Types::JobShopData Details::mJobShopData;
    std::vector< std::vector< int > > Details::mReadDataFromFile;


    std::vector< std::vector< int > > Details::DataFromFile()
    {
        return Details::mReadDataFromFile;
    }
}