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
    typedef unsigned int Kozdras;

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
            std::vector<unsigned int> & S();
            std::vector<unsigned int> & C();

            std::queue<TaskNumber> & Q();

            void initializeT();
            void initializeA();
            void initializeP();
            
            void fillLO();
            void fillOFs();
            void fillPI();
            void fillPS();
            void fillLP();

            void prepareQueue();
            void countCmax();

            void set_S_C_Size();

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

            std::vector<unsigned int> mS; //czas startu danej operacji
            std::vector<unsigned int> mC; //czas konca danej operacji

            std::queue<TaskNumber> mQ;

            std::vector<Kozdras> tests;
            std::vector<Kozdras> singleton;
            std::vector<Kozdras> planista;
            std::vector<Kozdras> recoveryAction;
            // ;)
            
            void incrementOFs(int index);
            unsigned int sumLO(int index);
            unsigned int getAndPopFrontElementFromQueue();
            void calculate_S_C_values_for_operation(unsigned int operation);
            unsigned int findTechgnologicalAntecessor(unsigned int operation);
            unsigned int findMachineAntecessor(unsigned int opeartion);
            void updateS(unsigned int operation, unsigned int technological, unsigned int machine);
            void updateC(unsigned int operation, unsigned int technological, unsigned int machine);
            void updateLP(int operation);
    };
}