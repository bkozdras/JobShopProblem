#include "Details.hpp"

#include <string>

namespace Details
{
    std::istream & operator >> (std::istream & iStream, FileLine & fileLine)
    {
        std::getline(iStream, fileLine.mData);
        return iStream;
    }

    FileLine::operator std::string() const
    {
        return mData;
    }
}