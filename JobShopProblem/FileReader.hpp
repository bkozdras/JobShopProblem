#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Utilities
{
    class FileReader
    {
        public:

            static std::shared_ptr<FileReader> Instance();
            ~FileReader();

            bool readData(const std::string fileName);
            const std::vector< std::string > & getReadData() const;

        private:

            FileReader();

            FileReader(const FileReader &) = delete;
            FileReader & operator=(const FileReader &) = delete;

            static std::shared_ptr<FileReader> mInstance;
            std::vector< std::string > mReadData;
    };
}