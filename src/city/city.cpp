#include "city.h"

City::City()
{

}

City::~City()
{
    for (Building* building: m_builtBuildings)
    {
        delete building;
    }

    for (Building* building: m_availableBuildings)
    {
        delete building;
    }
}

void City::newTurnCityUpdate()
{
    newTurnFoodUpdate();
    //todo: add change of population effect on production
    newTurnProdUpdate();
}

void City::newTurnFoodUpdate()
{
    m_currentFood += m_currentFoodPerTurn;
    int foodThreshold = nextLevelFoodThreshold();

    // case level up
    if (m_currentFood >= foodThreshold)
    {
        m_currentFood -= foodThreshold;
        m_level++;
        //todo: manage multiple level up
    }
    // case level down
    else if (m_currentFood < 0)
    {
        m_level--;
        m_currentFood = nextLevelFoodThreshold() + m_currentFood;
    }
}

void City::newTurnProdUpdate()
{
    if (!m_currentBuilding)
    {
        m_surplusProd += m_currentProdPerTurn;
        return;
    }

    m_currentBuilding->investProduction(m_currentProdPerTurn);
    if (m_currentBuilding->isFinished())
    {
        m_surplusProd = m_currentBuilding->surplusInvestment();
        m_currentBuilding = nullptr;
    }
}


int City::nextLevelFoodThreshold()
{
    return 6+4*(m_level-1);
}
