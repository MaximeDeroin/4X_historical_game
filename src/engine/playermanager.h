#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "../city/city.h"
#include "../unit/unit.h"

/*!
 * \brief Stores information of a player.
 */
class PlayerManager
{
public:
    explicit PlayerManager(int playerNumber);

    ~PlayerManager();

private:
    int m_playerNumber;
    QVector<Unit*> m_units; //!< List of units;
    QVector<City*> m_cities; //!< List of cities;
};

#endif // PLAYERMANAGER_H
