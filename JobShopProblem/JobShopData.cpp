#include "JobShopData.hpp"

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

    std::vector< TaskNumber > & JobShopData::PI()
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

    void JobShopData::initializeT()
    {
        mT.clear();

        unsigned int vectorSize = mNumerOfMachines * mNumberOfJobs + 1;

        mT.resize(vectorSize);

        for (int i = 1; i < vectorSize; i++)
        {
            if (0 != (i % mNumberOfJobs))
            {
                mT[i] = i + 1;
            }
        }
    }

    void JobShopData::initializeA(std::vector< std::vector<int> > fileContent)
    {
        mA.clear();
        mA.push_back(0);

        unsigned int startRow = 1;

        for (auto i = startRow; i < fileContent.size(); i++)
        {
            for (auto j = 0; j < fileContent[i].size(); j++)
            {
                if (j % 2 == 0)
                {
                    mA.push_back(fileContent[i][j]);
                }
            }
        }
    }

    void JobShopData::initializeP(std::vector< std::vector<int> > fileContent)
    {
        mP.clear();
        mP.push_back(0);

        unsigned int startRow = 1;

        for (auto i = startRow; i < fileContent.size(); i++)
        {
            for (auto j = 0; j < fileContent[i].size(); j++)
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

        for (auto i = 1; i < vectorSize; ++i)
        {
            mLO[mA[i]]++;
        }
    }

    void JobShopData::fillOFs()
    {
        mOFs.resize(mNumerOfMachines + 1);
        mOFs[0] = 0;

        for (auto i = 1; i < mNumerOfMachines+1; ++i)
        {
            mOFs[i] = sumLO(i) + i;
        }
    }

    void JobShopData::fillPI()
    {
        mPI.clear();
        mPI.resize(mNumerOfMachines*mNumberOfJobs + mNumerOfMachines + 1);

        for (int i = 1; i < mNumberOfJobs*mNumerOfMachines + 1; i++)
        {
            mPI[mOFs[mA[i]]] = i; // <3  ;)
            incrementOFs(mA[i]);
        }
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
}