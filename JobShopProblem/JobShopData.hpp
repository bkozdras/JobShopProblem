#pragma once

#include <vector>
#include <list>
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
            std::list<std::pair<int, int>> & PH2();
            std::vector<TaskTime> & S();
            std::vector<TaskTime> & C();
            std::vector<CriticalTask> & CriticalPath();
            std::vector<unsigned int> & CurrentBestPI();

            std::queue<TaskNumber> & Q();
            std::vector<std::pair<int, int>> & TabuList(){ return mTabuList; }

            void initializeT();
            void initializeA();
            void initializeP();
            void initializePh();
            void initializePh2();
            void initializeS();
            void initializeC();
            void initializeCriticalPath();
            
            void fillLO();
            void fillOFs();
            void fillPI();
            void fillPS();
            void fillLP();
            void fillPH();
            void fillPH2();
            void fillCriticalPath();

            void prepareQueue();
            void countCmax();

			bool initialize();
            bool calculateTables();

			void setSAndCSize();

            void createCriticalPath();


            ////do innej klasy
            void AlgorytmZstepujacy();
            void TabuSearch();
            //do tabu search
            bool elementInTabuList(const std::pair<int, int>& element);

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
            std::list<std::pair<int,int>> mPh2;
            std::vector<CriticalTask> mCriticalPath;

            std::vector<TaskTime> mS; //czas startu danej operacji
            std::vector<TaskTime> mC; //czas konca danej operacji

            std::vector<std::pair<int, int>> mTabuList; // lista tabu

            std::queue<TaskNumber> mQ;
            std::vector<unsigned int> mCurrentBestPI;
            
            void incrementOFs(int index);
            unsigned int sumLO(int index);
            unsigned int getAndPopFrontElementFromQueue();
            void calculateSAndCValuesForOperation(unsigned int operation);
            unsigned int findTechgnologicalAntecessor(unsigned int operation);
            unsigned int findMachineAntecessor(unsigned int opeartion);
			void updateS(unsigned int operation, unsigned int technologicalAntecessor, MachineNumber machineAntecessor);
            void updateC(unsigned int operation);
            void updateLP(int operation);

            TaskTime getIndexOfMaximumTaskFromC() const;

            std::vector<std::pair<int, int>> geneateAllPossibleChangesInBlock(std::pair<int, int> pair);
            
    };
}