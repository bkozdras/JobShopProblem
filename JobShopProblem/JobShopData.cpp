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
        mPS.resize(mNumberOfJobs*mNumerOfMachines+1);

        for (decltype(mPI.size()) i = 0; i < mPI.size(); ++i)
        {
            mPS[mPI[i]] = i;
        }
    }

    void JobShopData::fillLP()
    {
        mLp.resize(mNumberOfJobs*mNumerOfMachines + 1);

        for (decltype(mT.size()) i = 1;  i < mT.size();  i++)
        {
            mLp[mT[i]]++;
        }

        int ns;
        for (decltype(mPS.size()) i = 1; i < mPS.size(); i++)
        {
            ns = mPI[mPS[i] + 1];
            mLp[ns]++;
        }
    }

    void JobShopData::fillPH()
    {
        TaskNumber techAnt; // technological antecessor
        TaskNumber machAnt; // machine antecessor

        for (NumberOfJobs i = 1; i < mNumberOfJobs * mNumerOfMachines; i++)
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
                mPh[i] = techAnt;
            }
        }
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
}