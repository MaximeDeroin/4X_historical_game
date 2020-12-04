#ifndef CITY_H
#define CITY_H

#include <QVector>
#include "../building/building.h"

/*!
 * \brief Stores state of a city.
 */
class City
{
public:
    City();
    ~City();

    void newTurnCityUpdate();
    void newTurnFoodUpdate();
    void newTurnProdUpdate();

private:
    QString m_name;
    QVector<Building*> m_builtBuildings;
    QVector<Building*> m_availableBuildings;

    Building* m_currentBuilding;

    int m_level; //!< Level of the city
    int m_currentProdPerTurn; //!< Current production per turn of the city.
    int m_currentFood; //!< Current food produced at this level.
    int m_currentFoodPerTurn; //!< Current food per turn of the city.

    int m_surplusProd; //!< Surplus of production from ending a building construction.

    int nextLevelFoodThreshold(); //!< Amount of food to reach next level.
};

#endif // CITY_H
