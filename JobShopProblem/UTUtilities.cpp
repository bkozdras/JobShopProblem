#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "UTSettings.hpp"

#include <vector>
#include <string>
#include <fstream>

#include "Utilities.hpp"

namespace
{
    class Fixture
    {
    public:

        bool compareTwoVectors(const std::vector< std::vector< int > > first, std::vector< std::vector< int > > second)
        {
            if (first.size() != second.size())
            {
                return false;
            }

            for (unsigned int i = 0; i < first.size(); ++i)
            {
                const auto & firstElem = first.at(i);
                const auto & secondElem = second.at(i);

                if (firstElem.size() != secondElem.size())
                {
                    return false;
                }

                for (unsigned int j = 0; j < firstElem.size(); ++j)
                {
                    if (firstElem.at(j) != secondElem.at(j))
                    {
                        return false;
                    }
                }
            }

            return true;
        }
    };
}

BOOST_AUTO_TEST_SUITE(UT)

    BOOST_FIXTURE_TEST_SUITE(UtilitiesTests, Fixture)

        BOOST_AUTO_TEST_CASE(ReadLines_ShallReturnCorrectFileContent)
        {
            std::string filePath(UT_UTILITIES_FILE_PATH);

            std::vector<std::string> fileContent;
            std::ifstream fileStream;

            try
            {
                fileStream.open(filePath, std::ifstream::in);
            }
            catch (...)
            {
                BOOST_FAIL("File not found!");
            }

            BOOST_REQUIRE(fileStream.is_open());

            Utilities::readLines(fileStream, std::back_inserter(fileContent));
        }

        BOOST_AUTO_TEST_CASE(ConvertStringVectorToIntVectorVector_ShallProperConvert)
        {
            const std::vector< std::string > stringVector = { "1 2 3", "4 5 6 7", "7 8" };
            const std::vector< std::vector< int > > expectedOutputVector =
            {
                { 1, 2, 3 },
                { 4, 5, 6, 7 },
                { 7, 8 }
            };

            std::vector< std::vector< int > > outputVector;

            BOOST_REQUIRE(Utilities::StringParser::convert(stringVector, outputVector));

            BOOST_REQUIRE(compareTwoVectors(expectedOutputVector, outputVector));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()