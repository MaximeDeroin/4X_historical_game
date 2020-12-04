#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "playermanager.h"
#include "../gui/map/mapmanager.h"

/*!
 * \brief Stores the information of a game.
 */
class GameManager
{
public:
    explicit GameManager(int playerNumber = 1);

    bool openMap(const QString &filename);

    QVector<MapTile *> mapTiles() const;

private:
    int m_currentTurn; //!< Turn number.

    QVector<PlayerManager*> m_players; //!< List of players.

    MapManager* m_map;
};

#endif // GAMEMANAGER_H
