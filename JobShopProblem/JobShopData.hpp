#pragma once

#include <vector>

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
            std::vector< TaskNumber > & PI();
            std::vector< TaskPositionInPermutation > & PS();

            void initializeT();

        private:

            NumberOfJobs mNumberOfJobs;
            NumberOfMachines mNumerOfMachines;

            std::vector<TaskNumber> mT; // T
            std::vector<MachineNumber> mA; // A
            std::vector<TaskTime> mP; // P
            std::vector<NumberOfAntecessors> mLp; // Lp
            std::vector< TaskNumber > mPI; // PI
            std::vector< TaskPositionInPermutation > mPS; // PS
    };
}