#pragma once

#include <string>
#include <functional>
#include <vector>

namespace Types
{
    class JobShopData;
}

namespace Program
{
    class Details
    {
        public:

            static void DataFileName(const std::string & dataFileName);
            static void DataFileName(std::string && dataFileName);
            static std::string & DataFileName();
            static void ReadDataFromFile(std::vector< std::vector< int > > && readDataFromFile);
            static const std::vector< std::vector< int > > & ReadDataFromFile();

            static Types::JobShopData & JobShopData();

        private:

            static std::string mDataFileName;
            static Types::JobShopData mJobShopData;
            static std::vector< std::vector< int > > mReadDataFromFile;
    };
}