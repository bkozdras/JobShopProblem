#include "JobShopData.hpp"
#include "Data.hpp"
#include <algorithm>

namespace Types
{
    void JobShopData::setNumberOfJobs(NumberOfJobs numberOfJobs)
    {
        mNumberOfJobs = numberOfJobs;
    }

    NumberOfJobs JobShopData::getNumberOfJobs() const
    {
        return mNumberOfJobs;
    }

    void JobShopData::setNumberOfMachines(NumberOfMachines numberOfMachines)
    {
        mNumerOfMachines = numberOfMachines;
    }

    NumberOfMachines JobShopData::getNumberOfMachines() const
    {
        return mNumerOfMachines;
    }

    std::vector<TaskNumber> & JobShopData::T()
    {
        return mT;
    }

    std::vector<MachineNumber> & JobShopData::A()
    {
        return mA;
    }

    std::vector<TaskTime> & JobShopData::P()
    {
        return mP;
    }

    std::vector<NumberOfAntecessors> & JobShopData::Lp()
    {
        return mLp;
    }

    std::vector<int> & JobShopData::LO()
    {
        return mLO;
    }

    std::vector<unsigned int > & JobShopData::PI()
    {
        return mPI;
    }

    std::vector< TaskPositionInPermutation > & JobShopData::PS()
    {
        return mPS;
    }

    std::vector<int> & JobShopData::OFs()
    {
        return mOFs;
    }

    std::vector<CriticalTask> & JobShopData::PH()
    {
        return mPh; 
    }

    std::list<std::pair<int, int>> & JobShopData::PH2()
    {
        return mPh2;
    }

    std::queue<TaskNumber> & JobShopData::Q()
    {
        return mQ;
    }

    std::vector<unsigned int> & JobShopData::S()
    {
        return mS;
    }

    std::vector<unsigned int> & JobShopData::C()
    {
        return mC;
    }

    std::vector<CriticalTask> & JobShopData::CriticalPath()
    {
        return mCriticalPath;
    }

    std::vector<unsigned int> & JobShopData::CurrentBestPI()
    {
        return mCurrentBestPI;
    }

    void JobShopData::initializeT()
    {
        mT.clear();

        unsigned int vectorSize = mNumerOfMachines * mNumberOfJobs + 1;

        mT.resize(vectorSize);

        for (decltype(vectorSize) i = 1; i < vectorSize; i++)
        {
            if (0 != (i % mNumberOfJobs))
            {
                mT[i] = i + 1;
            }
        }
    }

    void JobShopData::initializeA()
    {
        mA.clear();
        mA.push_back(0);

        const auto & fileContent = Program::Details::ReadDataFromFile();

        decltype(fileContent.size()) startRow = 1;

        for (decltype(fileContent.size()) i = startRow; i < fileContent.size(); i++)
        {
            for (decltype(i) j = 0; j < fileContent[i].size(); j++)
            {
                if (j % 2 == 0)
                {
                    mA.push_back(fileContent[i][j]);
                }
            }
        }
    }

    void JobShopData::initializeP()
    {
        mP.clear();
        mP.push_back(0);

        const auto & fileContent = Program::Details::ReadDataFromFile();

        decltype(fileContent.size()) startRow = 1;

        for (decltype(fileContent.size()) i = startRow; i < fileContent.size(); i++)
        {
            for (decltype(i) j = 0; j < fileContent[i].size(); j++)
            {
                if (j % 2 == 1)
                {
                    mP.push_back(fileContent[i][j]);
                }
            }
        }
    }

    void JobShopData::initializePh()
    {
        mPh.resize( mNumberOfJobs * mNumerOfMachines + 1 );
    }

    void JobShopData::initializePh2()
    {
        mPh2.resize(mNumberOfJobs * mNumerOfMachines + 1);
    }

    void JobShopData::initializeC()
    {
        mC.resize(mNumberOfJobs * mNumerOfMachines + 1);
    }

    void JobShopData::initializeS()
    {
        mS.resize(mNumberOfJobs * mNumerOfMachines + 1);
    }

    void JobShopData::initializeCriticalPath()
    {
        mCriticalPath.resize( mNumberOfJobs * mNumerOfMachines + 1 );
    }

    void JobShopData::fillLO()
    {
        unsigned int vectorSize = mNumberOfJobs*mNumerOfMachines + 1;
        mLO.clear();
        mLO.resize(mNumerOfMachines + 1);

        for (decltype(vectorSize) i = 1; i < vectorSize; ++i)
        {
            mLO[mA[i]]++;
        }
    }

    void JobShopData::fillOFs()
    {
        mOFs.clear();
        mOFs.resize(mNumerOfMachines + 1);
        mOFs[0] = 0;

        for (decltype(mNumerOfMachines) i = 1; i < mNumerOfMachines + 1; ++i)
        {
            mOFs[i] = sumLO(i) + i;
        }
    }

    void JobShopData::fillPI()
    {
        mPI.clear();
        mPI.resize(mNumerOfMachines*mNumberOfJobs + mNumerOfMachines + 1);

        for (decltype(mNumberOfJobs) i = 1; i < mNumberOfJobs*mNumerOfMachines + 1; i++)
        {
            mPI[mOFs[mA[i]]] = i; // <3  ;)
            incrementOFs(mA[i]);
        }
    }

    void JobShopData::fillPS()
    {
        mPS.clear();
        mPS.resize(mNumberOfJobs*mNumerOfMachines+1);

        for (decltype(mPI.size()) i = 0; i < mPI.size(); ++i)
        {
            mPS[mPI[i]] = i;
        }
    }

    void JobShopData::fillLP()
    {
        mLp.clear();
        mLp.resize(mNumberOfJobs*mNumerOfMachines + 1);

        for (int i = 1;  i < mT.size();  i++)
        {
            mLp[mT[i]]++;
        }

        int ns;
        for (int i = 1; i < mPS.size(); i++)
        {
            ns = mPI[mPS[i] + 1];
            mLp[ns]++;
        }
    }

    void JobShopData::fillPH()
    {
        TaskNumber techAnt; // technological antecessor
        TaskNumber machAnt; // machine antecessor

        for (NumberOfJobs i = 1; i < mNumberOfJobs * mNumerOfMachines + 1; i++)
        {
            if (0 == mT[i - 1])
            {
                techAnt = 0;
            }
            else
            {
                techAnt = i - 1;
            }

            if (0 == mPI[mPS[i] - 1])
            {
                machAnt = 0;
            }
            else
            {
                machAnt = mPI[mPS[i] - 1];
            }

            if (mC[machAnt] > mC[techAnt])
            {
                mPh[i] = machAnt;
            }
            else
            {
                mPh[i] = techAnt;
            }
        }
    }

    void JobShopData::fillPH2()
    {
        mPh2.clear();
        int task1 = 0;
        int task2 = 0;

        if (mPS[mCriticalPath[1]] + 1 == mPS[mCriticalPath[2]])
            task1 = 1;

        for (auto i = 1; i < mCriticalPath.size() - 2; ++i)
        {
            //     poprz. technologiczny               nastepnik maszynowy
            if ((mCriticalPath[i + 1] == mT[mCriticalPath[i]]) && ((mPS[mCriticalPath[i + 1]] + 1) == mPS[mCriticalPath[i + 2]]))
            {
                task1 = i + 1;
            }

            //     poprz maszynowy                        nast.technologiczny
            if ((mPS[mCriticalPath[i]] + 1 == mPS[mCriticalPath[i + 1]]) && (mCriticalPath[i + 2] == mT[mCriticalPath[i + 1]] || (mCriticalPath[i + 1] == mCriticalPath[mCriticalPath.size()-1] )))
            {
                task2 = i+1;
            }

            if (task1 != 0 && task2 != 0)
            {
                mPh2.push_back(std::make_pair(std::min(task1, task2), std::max(task1, task2)));
                task1 = 0;
                task2 = 0;
            }

        }//koniec for
        if (mPS[mCriticalPath[mCriticalPath.size() - 2]] + 1 == mPS[mCriticalPath[mCriticalPath.size() - 1]])
        {
            task2 = mCriticalPath.size() - 1;
        }

        if (task1 != 0 && task2 != 0)
        {
            mPh2.push_back(std::make_pair(std::min(task1, task2), std::max(task1, task2)));
            task1 = 0;
            task2 = 0;
        }



        int a =0;
    }

    void JobShopData::fillCriticalPath()
    {
        //mCriticalPath.resize(mNumberOfJobs*mNumerOfMachines + 1);
        mCriticalPath.clear();
        TaskTime maxElementC = getIndexOfMaximumTaskFromC();
        TaskNumber techConsequent = mPh[ maxElementC ]; // technological consequent

        mCriticalPath.push_back(maxElementC);

        while (0 != techConsequent)
        {
            mCriticalPath.insert(mCriticalPath.begin(), techConsequent);
            techConsequent = mPh[techConsequent];
        }
        mCriticalPath.insert(mCriticalPath.begin(), 0);
        int a = 0;

    }

    void JobShopData::prepareQueue()
    {
        for (decltype(mLp.size()) i = 1; i < mLp.size(); ++i)
        {
            if (0 == mLp[i])
            {
                mQ.push(i);
            }
        }
    }

    void JobShopData::countCmax()
    {
        int top;

        while (!mQ.empty())
        {
            top = getAndPopFrontElementFromQueue();
            calculateSAndCValuesForOperation(top);
            updateLP(top);
        }
    }

    bool JobShopData::initialize()
    {
        try
        {
            initializeT();
            initializeA();
            initializeP();
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    bool JobShopData::calculateTables()
    {
        try
        {
            fillLO();
            fillOFs();
            fillPI();
            fillPS();
            fillLP();
            prepareQueue();
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    void JobShopData::setSAndCSize()
    {
        mS.resize( mNumerOfMachines * mNumberOfJobs + 1 );
        mC.resize( mNumberOfJobs * mNumerOfMachines + 1 );
    }

    unsigned int JobShopData::sumLO(int index)
    {
        if ((index - 1) == 0)
        {
            return 0;
        }

        unsigned int sum = 0;

        for (auto i = 0; i < index; i++)
        {
            sum += mLO[i];
        }

        return sum;
    }

    void JobShopData::incrementOFs(int index)
    {
        mOFs[index]++;
    }

    unsigned int JobShopData::getAndPopFrontElementFromQueue()
    {
        unsigned int elem = mQ.front();
        mQ.pop();
        return elem;
    }

	void JobShopData::calculateSAndCValuesForOperation(unsigned int operation)
    {
        unsigned int technologicalAntecessor = findTechgnologicalAntecessor(operation);
        unsigned int machineAntecessor = findMachineAntecessor(operation);
        updateS(operation, technologicalAntecessor, machineAntecessor);
        updateC(operation);
    }

    unsigned int JobShopData::findTechgnologicalAntecessor(unsigned int operation)
    {
        if (0 == mT[operation - 1])
        {
            return 0;
        }
        else
        {
            return operation - 1;
        }
    }

    unsigned int JobShopData::findMachineAntecessor(unsigned int operation)
    {
        if (0 == mPI[mPS[operation] - 1])
        {
            return 0;
        }
        else
        {
            return mPI[mPS[operation] - 1];
        }
    }

	void JobShopData::updateS(unsigned int operation, unsigned int technologicalAntecessor, MachineNumber machineAntecessor)
    {
		mS[operation] = std::max(mC[technologicalAntecessor], mC[machineAntecessor]);
    }

	void JobShopData::updateC(unsigned int operation)
    {
        mC[operation] = mS[operation] + mP[operation];
    }

    void JobShopData::updateLP(int operation)
    {
        int ns;

        ns = mPI[mPS[operation] + 1];

        if (0 != ns)
        {
            mLp[ns]--;
        }
        if (0 == mLp[ns])
        {
            mQ.push(ns);
        }

        ns = mT[operation];
        if (0 != ns)
        {
            mLp[ns]--;
        }
        if (0 == mLp[ns])
        {
            mQ.push(ns);
        }
    }

    TaskTime JobShopData::getIndexOfMaximumTaskFromC() const
    {
        return std::distance(mC.begin(), std::max_element(mC.begin(), mC.end()));
    }

    ///// do innej klasy
    void JobShopData::AlgorytmZstepujacy()
    {    
        unsigned int task1, task2;
        std::vector<unsigned int> tmpCmax; //wektor Cmax'ow dla dla kazdej zamiany z listy Ph2
        tmpCmax.clear();
        tmpCmax.resize(mPh2.size());

        //przepisanie tablicy pi wyliczonej przez poprzedni algorytm
        mCurrentBestPI = mPI;
        //zapamietanie wstepnego Cmax
        unsigned int globalCmax = *std::max_element(mC.begin(), mC.end());
        bool isChanged = true;


        while (isChanged)
        {
            for (auto i = 0; i < mPh2.size(); ++i)
            {
                auto iterator = mPh2.begin();
                std::advance(iterator, i); // przesun iterator o i ???
                task1 = std::get<0>(*iterator);
                task2 = std::get<1>(*iterator);
                std::swap(mPI[mPS[mCriticalPath[task1]]], mPI[mPS[mCriticalPath[task2]]]);

                //oO
                fillPS();
                fillLP();
                prepareQueue();
                countCmax();
                tmpCmax[i] = *std::max_element(mC.begin(), mC.end());

                mPI = mCurrentBestPI;
            }

            //indeks elemetu z tablicy tmpCmax o najmniejszym Cmaxie po zamianie
            unsigned int IndexOfMinCmax = std::distance(tmpCmax.begin(), std::min_element(tmpCmax.begin(), tmpCmax.end()));

            //czy nastapila globalna poprawa
            if (globalCmax > tmpCmax[IndexOfMinCmax])
            {
                globalCmax = tmpCmax[IndexOfMinCmax];
                
                auto iterator = mPh2.begin();
                std::advance(iterator, IndexOfMinCmax); // przesun iterator o i ???
                task1 = std::get<0>(*iterator);
                task2 = std::get<1>(*iterator);
                std::swap(mPI[mPS[task1]], mPI[mPS[task2]]);
                mCurrentBestPI = mPI;
                mPh2.clear();

                fillPS();
                fillLP();
                prepareQueue();
                countCmax();
                fillPH();
                fillCriticalPath();
                fillPH2();
            }
            else
            {
                isChanged = false;
            }
        }
    }

    //TABU SEARCH
    void JobShopData::TabuSearch()
    {
        const unsigned int tabuListLength = 7;
        unsigned int iterations = 1000;
        unsigned int task1, task2;
        mPh2.clear();

        //przepisanie tablicy pi wyliczonej przez poprzedni algorytm
        std::vector<unsigned int>originalPI = mPI;
        mCurrentBestPI = mPI;

        std::pair<int, int> BestMove;
        unsigned int BestCmax = *std::max_element(mC.begin(), mC.end());;
 
        unsigned int BestTempCmax = 99999;
        unsigned int TempCmax = 99999;

        
        mTabuList.insert(mTabuList.begin(), tabuListLength, std::make_pair(0,0));

        
        for (auto i = 0; i < iterations; ++i)
        {
            fillPS();
            fillLP();
            prepareQueue();
            countCmax();
            fillPH();
            fillCriticalPath();
            fillPH2();

            for(auto& pair: mPh2)
            {
                std::vector < std::pair<int, int>> all_changes = geneateAllPossibleChangesInBlock(pair);
                //czy Ph2[i] jest na liscie tabu
                //if (std::min(Ph2[j], Ph2[j + 1]) == TabuList[k].first && std::max(Ph2[j], Ph2[j + 1]) == TabuList[k].second)
                if (false == elementInTabuList(pair))
                {

                    task1 = std::get<0>(pair);
                    task2 = std::get<1>(pair);
                    std::swap(mPI[mPS[mCriticalPath[task1]]], mPI[mPS[mCriticalPath[task2]]]);
                    fillPS();
                    fillLP();
                    prepareQueue();
                    countCmax();
                    TempCmax = *std::max_element(mC.begin(), mC.end());

                    if (BestTempCmax > TempCmax)
                    {
                        BestTempCmax = TempCmax;
                        BestMove = pair;
                    }
                    //odtworz pi
                    mPI = originalPI;
                }
            }

            
            //Ph2[0] = BestMove.first;
            //Ph2[1] = BestMove.second;
            //SwapPi(0);
            task1 = std::get<0>(BestMove);
            task2 = std::get<1>(BestMove);
            std::swap(mPI[mPS[mCriticalPath[task1]]], mPI[mPS[mCriticalPath[task2]]]);

            if (BestTempCmax < BestCmax)
            {
                mCurrentBestPI = mPI;
            }

            //for (int i = 0; i < OriginalPi.size(); i++)
            //{
            //    OriginalPi[i] = Pi[i];
            //}
            originalPI = mPI;
            mTabuList.pop_back();
            mTabuList.insert(mTabuList.begin(), 1, BestMove);
            ;
        }
    }

        bool JobShopData::elementInTabuList(const std::pair<int, int>& element)
        {
            const auto position = std::find(mTabuList.begin(), mTabuList.end(), element);

            return position == mTabuList.end() ? false : true;
        }

        std::vector<std::pair<int, int>> JobShopData::geneateAllPossibleChangesInBlock(std::pair<int, int> pair)
        {
            unsigned int task1 = std::get<0>(pair);
            unsigned int task2 = std::get<1>(pair);

            std::vector<std::pair<int, int>> result;

            for (auto i = task1; i < task2; ++i)
            {
                result.push_back(std::make_pair(mCriticalPath[i], mCriticalPath[i + 1]));
            }
            return result;
        }
}