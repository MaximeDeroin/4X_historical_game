#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "confreader/mapreader.h"

/*!
 * \brief Manages the map of the game.
 */
class MapManager
{
public:
    MapManager();

    /*!
     * \brief Opens a map file.
     * \param[in] filename Name of the map file.
     * \return True if successfull.
     */
    bool openMap(const QString &filename);

    QVector<MapTile *> mapTiles() const; //!< Getter of m_mapTiles.

    /*!
     * \brief Selects starting points for the players of the game.
     * Starting points have a distance of at least 6 between one another.
     * \param[in] playerNumber Number of player.
     * \return List of starting points for each player.
     */
    QVector<MapTile *> selectStartingPoints(int playerNumber);

    /*!
     * \brief Computes the distance between two tiles.
     * \param[in] first First tile.
     * \param[in] second Second tile.
     * \return Distance between two tiles.
     */
    int distance(MapTile* first, MapTile* second);

private:
    int m_mapWidth; //!< Width of the map.
    int m_mapHeight; //!< Height of the map.

    QVector<MapTile *> m_mapTiles; //!< List of map tiles.

    /*!
     * \brief Selects map tiles where a player can start.
     * \return Vector of tiles where the player can start.
     */
    QVector<MapTile *> potentialStartingTiles();
};

#endif // MAPMANAGER_H
