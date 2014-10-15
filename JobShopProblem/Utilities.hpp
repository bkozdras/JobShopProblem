#pragma once

#include <istream>
#include <algorithm>
#include <vector>
#include <string>

#include "Details.hpp"

namespace Utilities
{
    template <class OutIterator>
    void readLines(std::istream & iStream, OutIterator destIterator)
    {
        typedef std::istream_iterator<Details::FileLine> InIterator;
        std::copy(InIterator(iStream), InIterator(), destIterator);
    }

    namespace StringParser
    {
        bool convert(const std::vector< std::string > &  inputData, std::vector< std::vector< int > > & outputData);
    }
}