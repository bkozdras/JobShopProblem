#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/assign/std/queue.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/assign/list_of.hpp>
#include "UTSettings.hpp"

#include "JobShopData.hpp"
#include "Data.hpp"

namespace
{
    class JobShopDataFixture
    {
        public :


    };
}

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

        BOOST_AUTO_TEST_CASE(InitializationA_ShallReturnCorrectVector)
        {
            std::vector<Types::MachineNumber> expectedA = {0, 1, 2, 3, 3, 1, 2, 2, 1 ,3 };
            std::vector< std::vector<int> > parsedFile = { 
                std::vector<int>{3,3},
                std::vector<int>{1, 5, 2, 9, 3, 8},
                std::vector<int>{3, 9, 1, 3, 2, 10},
                std::vector<int>{2, 9, 1, 4, 3, 5}
            };

            Program::Details::ReadDataFromFile(std::move(parsedFile));
            Program::Details::JobShopData().initializeA();


            BOOST_REQUIRE(Program::Details::JobShopData().A().size() == expectedA.size());

            for (decltype(Program::Details::JobShopData().A().size()) i = 0; i < Program::Details::JobShopData().A().size(); i++)
            {
                BOOST_REQUIRE(Program::Details::JobShopData().A().at(i) == expectedA[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(InitializationP_ShallReturnCorrectVector)
        {
            std::vector<Types::MachineNumber> expectedP = { 0, 5, 9, 8, 9, 3, 10, 9, 4, 5};
            std::vector< std::vector<int> > parsedFile = {
                std::vector<int>{3, 3},
                std::vector<int>{1, 5, 2, 9, 3, 8},
                std::vector<int>{3, 9, 1, 3, 2, 10},
                std::vector<int>{2, 9, 1, 4, 3, 5}
            };

            Types::JobShopData jobShopData;

            jobShopData.initializeP();


            BOOST_REQUIRE(jobShopData.P().size() == expectedP.size());

            for (decltype(jobShopData.P().size()) i = 0; i < jobShopData.P().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.P().at(i) == expectedP[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(FillLO_ShallReturnCorrectVector)
        {
            std::vector<Types::MachineNumber> A = { 0, 1, 2, 3, 3, 1, 2, 2, 1, 3, 0 };
            std::vector<Types::MachineNumber> P = { 0, 5, 9, 8, 9, 3, 10, 9, 4, 5, 0 };
            std::vector<int> expectedLO = { 0, 3, 3, 3};

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);

            jobShopData.A() = A;
            jobShopData.P() = P;

            jobShopData.fillLO();

            BOOST_REQUIRE(jobShopData.LO().size() == expectedLO.size());

            for (decltype(jobShopData.LO().size()) i = 0; i < jobShopData.LO().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.LO().at(i) == expectedLO[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(FillOFs_ShallReturnCorrectVector)
        {
            std::vector<int> LO = { 0, 3, 3, 3};
            std::vector<int> expectedOFs = { 0, 1, 5, 9 };

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.LO() = LO;
     
            jobShopData.fillOFs();
            
            BOOST_REQUIRE(jobShopData.OFs().size() == expectedOFs.size());

            for (decltype(jobShopData.OFs().size()) i = 0; i < jobShopData.OFs().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.OFs().at(i) == expectedOFs[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(FillPI_ShallReturnCorrectVector)
        {
            std::vector<Types::MachineNumber> A = { 0, 1, 2, 3, 3, 1, 2, 2, 1, 3};
            std::vector<Types::MachineNumber> P = { 0, 5, 9, 8, 9, 3, 10, 9, 4, 5};
            std::vector<int> LO = { 0, 3, 3, 3 };
            std::vector<int> OFs = { 0, 1, 5, 9 };
            std::vector<int> expectedPI = {0, 1, 5, 8, 0, 2, 6, 7, 0, 3, 4, 9, 0};

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.A() = A;
            jobShopData.P() = P;
            jobShopData.LO() = LO;
            jobShopData.fillOFs();
            jobShopData.fillPI();     

            BOOST_REQUIRE(jobShopData.PI().size() == expectedPI.size());

            for (decltype(jobShopData.PI().size()) i = 0; i < jobShopData.PI().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.PI().at(i) == expectedPI[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(FillPS_ShallReturnCorrectVector)
        {
            std::vector<Types::TaskPositionInPermutation> PI = { 0, 1, 5, 8, 0, 2, 6, 7, 0, 3, 4, 9, 0 };
            std::vector<int> expectedPS = {12,1,5,9,10,2,6,7,3,11};

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.PI() = PI;
            jobShopData.fillPS();


            BOOST_REQUIRE(jobShopData.PS().size() == expectedPS.size());

            for (decltype(jobShopData.PS().size()) i = 0; i < jobShopData.PS().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.PS().at(i) == expectedPS[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(FillLP_ShallReturnCorrectVector)
        {
            std::vector<unsigned int> PS = {12, 1, 5, 9, 10, 2, 6, 7, 3, 11 };
            std::vector<Types::TaskPositionInPermutation> PI = { 0, 1, 5, 8, 0, 2, 6, 7, 0, 3, 4, 9, 0 };
            std::vector<Types::TaskNumber> T = { 0, 2, 3, 0, 5, 6, 0, 8, 9, 0 };
            std::vector<Types::NumberOfAntecessors> expectedLP = { 6, 0, 1, 1, 1, 2, 2, 1, 2, 2 };

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.T() = T;
            jobShopData.PS() = PS;
            jobShopData.PI() = PI;
            jobShopData.fillLP();
    
            BOOST_REQUIRE(jobShopData.Lp().size() == expectedLP.size());

            for (decltype(jobShopData.Lp().size()) i = 0; i < jobShopData.Lp().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.Lp().at(i) == expectedLP[i]);;
            }
        }

        BOOST_AUTO_TEST_CASE(PrepareQueue_ShallReturnCorrectQueue)
        {
            std::vector<Types::NumberOfAntecessors> LP = { 6, 0, 1, 1, 1, 2, 2, 1, 2, 2 };
            std::queue<Types::TaskNumber> expectedQ = boost::assign::list_of(1).to_adapter( expectedQ );

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.Lp() = LP;
            jobShopData.prepareQueue();

            BOOST_REQUIRE(jobShopData.Q().size() == expectedQ.size());

            for (decltype(jobShopData.Q().size()) i = 0; i < jobShopData.Q().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.Q()._Get_container().at(i) == expectedQ._Get_container().at(i));

            }
        }

        BOOST_AUTO_TEST_CASE(PrepareQueue_ShallReturnCorrectQueueBasedOnProvidedInputData)
        {
            std::vector<Types::NumberOfAntecessors> LP = { 6, 0, 1, 1, 1, 0, 2, 0, 2, 2 };
            std::queue<Types::TaskNumber> expectedQ = boost::assign::list_of(1)(5)(7).to_adapter( expectedQ );

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.Lp() = LP;
            jobShopData.prepareQueue();

            BOOST_REQUIRE(jobShopData.Q().size() == expectedQ.size());

            for (decltype(jobShopData.Q().size()) i = 0; i < jobShopData.Q().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.Q()._Get_container().at(i) == expectedQ._Get_container().at(i));
            }
        }

  /*      BOOST_AUTO_TEST_CASE(ElementInTabuList_ElementIsOnList_ShallReturnTrue)
        {
            Types::JobShopData jobShopData;
            jobShopData.TabuList
            std::pair<int, int> pair = std::make_pair(7, 5);

            BOOST_REQUIRE(false == jobShopData.elementInTabuList(pair));

        }
*/
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()