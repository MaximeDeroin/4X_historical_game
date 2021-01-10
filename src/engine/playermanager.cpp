#include "playermanager.h"

PlayerManager::PlayerManager(int playerNumber):
    m_playerNumber(playerNumber),
    m_cities()
{

}

PlayerManager::~PlayerManager()
{
    for (Unit* unit: m_units)
    {
        delete unit;
    }
    for (City* city: m_cities)
    {
        delete city;
    }
}

void PlayerManager::setStartingPosition(MapTile *statingTile)
{

}

void PlayerManager::addUnit(Unit *unitType, MapTile *unitPosition)
{
    Unit* newUnit = new Unit(*unitType);
    newUnit->setPlayerNumber(m_playerNumber);
    m_units.push_back(newUnit);
    unitPosition->setUnit(newUnit);
}
