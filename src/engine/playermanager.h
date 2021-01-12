#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "../city/city.h"
#include "../unit/unit.h"
#include "../gui/map/maptile.h"

/*!
 * \brief Stores information of a player.
 */
class PlayerManager
{
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] playerNumber Number of the player.
     */
    explicit PlayerManager(int playerNumber);

    ~PlayerManager(); //!< Default destructor.

    /*!
     * \brief Sets starting tile position of the player.
     * \param[in] statingTile Starting tile position of the player
     */
    void setStartingPosition(MapTile* statingTile);

    void addUnit(Unit* unitType, MapTile* unitPosition);

private:
    int m_playerNumber; //!< Number of the player.
    QVector<Unit*> m_units; //!< List of units.
    QVector<City*> m_cities; //!< List of cities.

    QColor m_color; //!< Player color.

    QColor playerColor();
};

#endif // PLAYERMANAGER_H
