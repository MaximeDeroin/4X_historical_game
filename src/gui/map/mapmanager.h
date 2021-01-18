#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QObject>
#include "confreader/mapreader.h"

/*!
 * \brief Manages the map of the game.
 */
class MapManager : public QObject
{
    Q_OBJECT
public:
    MapManager(); //!< Default constructor.

    ~MapManager() = default; //!< Default destructor.

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

    /*!
     * \brief Moves a unit from a tile to another if the destination does not contain a unit.
     * \param[in] origin Origin tile.
     * \param[in] destination Destination tile.
     */
    void moveUnit(MapTile *origin, MapTile *destination);

signals:
    /*!
     * \brief Request a unit move to the game manager.
     * \param[in] origin Origin tile.
     * \param[in] destination Destination tile.
     */
    void requestMoveUnit(MapTile *origin, MapTile *destination);

public slots:

    /*!
     * \brief Reacts to a change of player.
     * \param[in] playerNumber New player number.
     */
    void currentPlayerChanged(int PlayerNumber);

private slots:
    /*!
     * \brief Triggered by a tile pressed.
     */
    void onTilePressed();

    /*!
     * \brief Triggered by a tile released.
     */
    void onTileReleased();

    /*!
     * \brief Triggered by the selection of a unit.
     * \param[in] unit Unit selected.
     */
    void onUnitSelected(Unit* unit);

    /*!
     * \brief Triggered by the end of selection of a unit.
     */
    void onUnitUnselected();

private:
    int m_mapWidth; //!< Width of the map.
    int m_mapHeight; //!< Height of the map.

    MapTile* m_currentTilePressed; //!< @todo see if useful
    MapTile* m_currentlySelectedTile; //!< @todo see if useful

    QVector<MapTile *> m_mapTiles; //!< List of map tiles.
    QVector<MapTile *> m_highlightedCanBeReached; //!< Tiles highlighted has
                                                  //!< reachable by selected unit.

    /*!
     * \brief Establishes signal connections between map tiles and the map manager.
     */
    void connectMapTiles();

    /*!
     * \brief Selects map tiles where a player can start.
     * \return Vector of tiles where the player can start.
     */
    QVector<MapTile *> potentialStartingTiles();

    /*!
     * \brief Helper function that sets canBeReached to the tile at the (x,y) position.
     * \param[in] x Row number of the tile.
     * \param[in] y Column number of the tile.
     * \param[in] canBeReached Value to set.
     */
    void setCanBeReached(int x, int y, bool canBeReached);

    /*!
     * \brief Indicates if the tile at (x,y) position is in the map.
     * \param[in] x Row number of the tile.
     * \param[in] y Column number of the tile.
     * \return True if x (resp y) is positive and less than the map width (resp height).
     */
    bool isInMap(int x, int y);

    /*!
     * \brief Set canBeReached to all the neighbors of the tile at the (x,y) position.
     * \param[in] x Row number of the tile.
     * \param[in] y Column number of the tile.
     * \param[in] canBeReached Value to set.
     */
    void setNeighborsCanBeReached(int x, int y, bool canBeReached);

    /*!
     * \brief Remove all tiles from tiles highlighted has reachable by selected unit.
     */
    void clearHighlightedCanBeReachedTiles();
};

#endif // MAPMANAGER_H
