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
    City(); //!< Default constructor.

    ~City(); //!< Default destructor.

    /*!
     * \brief Update city on new turn.
     */
    void newTurnCityUpdate();

    /*!
     * \brief Update food related parameters of the city on new turn.
     */
    void newTurnFoodUpdate();

    /*!
     * \brief Update production related parameters of the city on new turn.
     */
    void newTurnProdUpdate();

    int level() const; //!< Getter of m_level.

    int nextLevelFoodThreshold(); //!< Amount of food to reach next level.

    int currentFood() const; //!< Current food produced at this level.

private:
    QString m_name; //!< Name of the city.
    QVector<Building*> m_builtBuildings; //!< List of built buildings.
    QVector<Building*> m_availableBuildings; //!< List of available buildings.

    Building* m_currentBuilding; //!< Current building being built.

    int m_level; //!< Level of the city
    int m_currentProdPerTurn; //!< Current production per turn of the city.
    int m_currentFood; //!< Current food produced at this level.
    int m_currentFoodPerTurn; //!< Current food per turn of the city.

    int m_surplusProd; //!< Surplus of production from ending a building construction.

};

#endif // CITY_H
