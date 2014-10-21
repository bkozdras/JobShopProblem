#pragma once

#include <vector>
#include <iostream>
#include <queue>

namespace Types
{
    typedef unsigned int NumberOfJobs;
    typedef unsigned int NumberOfMachines;

    typedef unsigned int TaskNumber;
    typedef unsigned int MachineNumber;
    typedef unsigned int TaskPositionInPermutation;
    typedef unsigned int NumberOfAntecessors;
    typedef unsigned int TaskTime;

    class JobShopData
    {
        public:

            void setNumberOfJobs(NumberOfJobs numberOfJobs);
            NumberOfJobs getNumberOfJobs() const;

            void setNumberOfMachines(NumberOfMachines numberOfMachines);
            NumberOfMachines getNumberOfMachines() const;

            std::vector<TaskNumber> & T();
            std::vector<MachineNumber> & A();
            std::vector<TaskTime> & P();
            std::vector<NumberOfAntecessors> & Lp();
            std::vector<int> & LO();
            std::vector<int> & OFs();
            std::vector<unsigned int > & PI();
            std::vector< TaskPositionInPermutation > & PS();
            std::vector<int> & PH();

            std::vector<TaskNumber> & Q();

            void initializeT();
            void initializeA();
            void initializeP();
            
            void fillLO();
            void fillOFs();
            void fillPI();
            void fillPS();
            void fillLP();

        private:

            NumberOfJobs mNumberOfJobs;
            NumberOfMachines mNumerOfMachines;

            std::vector<TaskNumber> mT; // T
            std::vector<MachineNumber> mA; // A
            std::vector<TaskTime> mP; // P
            std::vector<NumberOfAntecessors> mLp; // Lp
            std::vector<int> mLO;
            std::vector<unsigned int > mPI; // PI
            std::vector< TaskPositionInPermutation > mPS; // PS
            std::vector<int> mOFs;
            std::vector<int> mPh;

            std::vector<TaskNumber> mQ;
            
            void incrementOFs(int index);
            unsigned int sumLO(int index);

    };
}