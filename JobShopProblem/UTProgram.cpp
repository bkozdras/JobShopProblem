#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "UTSettings.hpp"

#include "ProgramController.hpp"
#include "FileReader.hpp"
#include "Data.hpp"

BOOST_AUTO_TEST_SUITE(UT)

    BOOST_AUTO_TEST_SUITE(ProgramTests)

        BOOST_AUTO_TEST_CASE(CompleteTest_ShallPass)
        {
            const std::string testedFileName(UT_PROGRAM_TA01_PATH);
            Program::Details::DataFileName(testedFileName);

            ProgramController::initialize
            (
                {
                    ProgramController::TaskName::ReadData,
                    ProgramController::TaskName::ParseData,
                    ProgramController::TaskName::InitializeJobShopData,
                    ProgramController::TaskName::CalculateJobShopTables
                }
            );

            BOOST_REQUIRE_EQUAL(ProgramController::ExecuteResult::Success, ProgramController::run());
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()