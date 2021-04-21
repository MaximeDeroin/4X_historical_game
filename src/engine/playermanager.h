#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "../city/city.h"
#include "../unit/unit.h"
#include "../gui/map/maptile.h"

/*!
 * \brief Stores information of a player.
 */
class PlayerManager: public QObject
{
    Q_OBJECT
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

    /*!
     * \brief Adds a unit on a tile for the current player.
     * \param[in] unitType Unit type to add.
     * \param[in] unitPosition Position too add the unit to.
     */
    void addUnit(Unit* unitType, MapTile* unitPosition);

    /*!
     * \brief Adds a city on a tile for the current player.
     * \param[in] position Position too add the city to.
     */
    void addCity(MapTile* position);

    /*!
     * \brief Process begin turn events.
     * For example, apply production to current buildings.
     */
    void processBeginTurnEvents();

    /*!
     * \brief Reset unit movements and process end turn events.
     */
    void processEndTurnEvents();

signals:
    /*!
     * \brief Indicates a city creation.
     * \param[in] position Position of the city created.
     */
    void cityCreated(MapTile *position);

private:
    int m_playerNumber; //!< Number of the player.
    QVector<Unit*> m_units; //!< List of units.
    QVector<City*> m_cities; //!< List of cities.

    QColor m_color; //!< Player color.

    /*!
     * \brief Defines color for each player.
     * \return Color of the current player.
     */
    QColor playerColor();
};

#endif // PLAYERMANAGER_H
