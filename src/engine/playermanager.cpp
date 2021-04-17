#include "playermanager.h"

PlayerManager::PlayerManager(int playerNumber):
    m_playerNumber(playerNumber),
    m_units(),
    m_cities(),
    m_color(playerColor())
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
    newUnit->setPlayerColor(m_color);
    m_units.push_back(newUnit);
    unitPosition->setUnit(newUnit);

    //addCity(unitPosition);
}

void PlayerManager::addCity(MapTile *position)
{
    if (!position->city()) //TODO : change city creation condition
    {
        City* newCity = new City();
//    newCity->setCityColor(m_color);
        m_cities.push_back(newCity);
        position->setCity(newCity);
    }
}

void PlayerManager::processBeginTurnEvents()
{
    for (City* city: m_cities)
    {
        city->newTurnCityUpdate();
    }
}

void PlayerManager::processEndTurnEvents()
{
    for (Unit* unit: m_units)
    {
        unit->resetMovementPoints();
    }
}

QColor PlayerManager::playerColor()
{
    switch (m_playerNumber)
    {
    case 1:
        return Qt::blue;
    case 2:
        return Qt::green;
    case 3:
        return Qt::yellow;
    case 4:
        return Qt::magenta;
    case 5:
        return Qt::cyan;
    case 6:
        return Qt::lightGray;
    case 7:
        return Qt::darkYellow;
    case 8:
        return Qt::darkCyan;
    default:
        return Qt::darkGreen;
    }
}
