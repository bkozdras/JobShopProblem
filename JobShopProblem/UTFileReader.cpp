#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "UTSettings.hpp"

#include "FileReader.hpp"

BOOST_AUTO_TEST_SUITE(UT)

    BOOST_AUTO_TEST_SUITE(FileReaderTests)

        BOOST_AUTO_TEST_CASE(ReadExampleData)
        {
            const std::string exampleFilePath = UT_UTILITIES_FILE_PATH;
            const unsigned int exampleFileLineNumbers = 4;

            BOOST_REQUIRE(Utilities::FileReader::Instance()->readData(exampleFilePath));
            
            unsigned int readLines = Utilities::FileReader::Instance()->getReadData().size();
            
            BOOST_REQUIRE(exampleFileLineNumbers == readLines);
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()