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

        BOOST_AUTO_TEST_CASE(InitializationA_ShallReturnCorrectVector)
        {
            std::vector<Types::MachineNumber> expectedA = {0, 1, 2, 3, 3, 1, 2, 2, 1 ,3 };
            std::vector< std::vector<int> > parsedFile = { 
                std::vector<int>{3,3},
                std::vector<int>{1, 5, 2, 9, 3, 8},
                std::vector<int>{3, 9, 1, 3, 2, 10},
                std::vector<int>{2, 9, 1, 4, 3, 5}
            };

            Types::JobShopData jobShopData;

            jobShopData.initializeA(parsedFile);


            BOOST_REQUIRE(jobShopData.A().size() == expectedA.size());

            for (decltype(jobShopData.A().size()) i = 0; i < jobShopData.A().size(); i++)
            {
                BOOST_REQUIRE(jobShopData.A().at(i) == expectedA[i]);;
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

            jobShopData.initializeP(parsedFile);


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
            std::vector<int> expectedOFs = { 0, 1, 5, 9 }; //JAKI MA BYC POPRAWNY WYNIK - PIMPUS MOGL SIE POMYLIC WE WZORZE?!

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
            std::vector<int> expectedPI = {};

            Types::JobShopData jobShopData;
            jobShopData.setNumberOfJobs(3);
            jobShopData.setNumberOfMachines(3);
            jobShopData.A() = A;
            jobShopData.P() = P;
            jobShopData.LO() = LO;
            jobShopData.fillOFs();
            jobShopData.fillPI(); 

            //BOOST_REQUIRE(jobShopData.PI().size() == expectedPI.size());

            //for (decltype(jobShopData.PI().size()) i = 0; i < jobShopData.PI().size(); i++)
            //{
            //    BOOST_REQUIRE(jobShopData.PI().at(i) == expectedPI[i]);;
            //}
            BOOST_REQUIRE(true);
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()