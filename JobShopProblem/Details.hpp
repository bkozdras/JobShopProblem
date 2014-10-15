#pragma once

#include <string>
#include <istream>

namespace Details
{
    class FileLine
    {
        public:

            friend std::istream & operator >> (std::istream & iStream, FileLine & fileLine);
            operator std::string() const;

        private:

            std::string mData;
    };
}