#include "Utilities.hpp"
#include <cassert>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <functional>
#include <algorithm>

namespace Utilities
{
    namespace StringParser
    {
        bool convert(const std::vector< std::string > &  inputData, std::vector< std::vector< int > > & outputData)
        {
            assert(!inputData.empty());
            outputData.clear();

            for (const auto & fileLine : inputData)
            {
                boost::char_separator< char > separator(" \t");
                boost::tokenizer< boost::char_separator< char > > tokens(fileLine, separator);

                std::vector<int> intTokens(std::distance(tokens.begin(), tokens.end()));
                try
                {
                    std::transform(tokens.begin(), tokens.end(), intTokens.begin(), boost::lexical_cast<int, std::string>);
                }
                catch (boost::bad_lexical_cast const &)
                {
                    return false;
                }

                outputData.push_back(std::move(intTokens));
            }

            return true;
        }
    }
}