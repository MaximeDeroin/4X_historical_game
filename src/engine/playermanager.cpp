#include "playermanager.h"

PlayerManager::PlayerManager():
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
