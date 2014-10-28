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
    typedef unsigned int CriticalTask;

	enum { Separator = 0U };

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
            std::vector<CriticalTask> & PH();
            std::vector<TaskTime> & S();
            std::vector<TaskTime> & C();

            std::queue<TaskNumber> & Q();

            void initializeT();
            void initializeA();
            void initializeP();
            
            void fillLO();
            void fillOFs();
            void fillPI();
            void fillPS();
            void fillLP();
            void fillPH();

            void prepareQueue();
            void countCmax();

			bool initialize();

			void setSAndCSize();

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
            std::vector<CriticalTask> mPh;

            std::vector<TaskTime> mS; //czas startu danej operacji
            std::vector<TaskTime> mC; //czas konca danej operacji

            std::queue<TaskNumber> mQ;
            
            void incrementOFs(int index);
            unsigned int sumLO(int index);
            unsigned int getAndPopFrontElementFromQueue();
            void calculateSAndCValuesForOperation(unsigned int operation);
            unsigned int findTechgnologicalAntecessor(unsigned int operation);
            unsigned int findMachineAntecessor(unsigned int opeartion);
			void updateS(unsigned int operation, unsigned int technologicalAntecessor, MachineNumber machineAntecessor);
            void updateC(unsigned int operation);
            void updateLP(int operation);
    };
}