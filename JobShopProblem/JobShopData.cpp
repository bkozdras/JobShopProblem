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

    std::vector< TaskNumber > & JobShopData::PI()
    {
        return mPI;
    }

    std::vector< TaskPositionInPermutation > & JobShopData::PS()
    {
        return mPS;
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
}