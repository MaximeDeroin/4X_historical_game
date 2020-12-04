#include "building.h"

Building::Building()
{

}

void Building::investProduction(int production)
{

}

int Building::surplusInvestment()
{
    // no surplus if building not finished
    if (!this->isFinished())
    {
        return 0;
    }
    else
    {
        return (m_productionInvested - m_constructionCost);
    }
}

int Building::constructionCost() const
{
    return m_constructionCost;
}

int Building::productionInvested() const
{
    return m_productionInvested;
}

bool Building::isFinished() const
{
    return (m_productionInvested <= m_constructionCost);
}
