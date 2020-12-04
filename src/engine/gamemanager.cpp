#include "gamemanager.h"

GameManager::GameManager(int playerNumber):
    m_currentTurn(0),
    m_map(new MapManager)
{
    for (int i = 0; i<playerNumber; i++)
    {
        m_players.push_back(new PlayerManager);
    }
}

bool GameManager::openMap(const QString &filename)
{
    return m_map->openMap(filename);
}

QVector<MapTile *> GameManager::mapTiles() const
{
    return m_map->mapTiles();
}
