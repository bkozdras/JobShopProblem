#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "UTSettings.hpp"

#include "JobShopData.hpp"

BOOST_AUTO_TEST_SUITE(UT)

    BOOST_AUTO_TEST_SUITE(JobShopDataTests)

        BOOST_AUTO_TEST_CASE(InitializationT_ShallReturnCorrectVector)
        {
            std::vector<Types::TaskNumber> expectedT = { 0, 2, 3, 0, 5, 6, 0, 8, 9, 0 };

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfMachines(3);
            jobShopData.setNumberOfJobs(3);

            jobShopData.initializeT();

            BOOST_REQUIRE(jobShopData.T().size() == expectedT.size());

            for (decltype(jobShopData.T().size()) i = 0; i < jobShopData.T().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.T().at(i) == expectedT[i]);;
            }
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()