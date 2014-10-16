#pragma once

#include <string>
#include <functional>
#include <vector>
#include "JobShopData.hpp"

namespace Program
{
    class Details
    {
        public:

            static void DataFileName(const std::string & dataFileName);
            static void DataFileName(std::string && dataFileName);
            static std::string & DataFileName();
            static void ReadDataFromFile(std::vector< std::vector< int > > && readDataFromFile);

            static Types::JobShopData & JobShopData();
            static std::vector< std::vector< int > > DataFromFile();

        private:

            static std::string mDataFileName;
            static Types::JobShopData mJobShopData;
            static std::vector< std::vector< int > > mReadDataFromFile;
    };
}