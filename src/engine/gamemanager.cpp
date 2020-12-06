#include "gamemanager.h"

GameManager::GameManager(int playerNumber, QObject *parent):
    QObject(parent),
    m_currentTurn(0),
    m_currentPlayer(0),
    m_map(new MapManager)
{
    if (playerNumber < MIN_PLAYER)
        playerNumber = MIN_PLAYER;

    if (playerNumber > MAX_PLAYER)
        playerNumber = MAX_PLAYER;

    for (int i = 0; i<playerNumber; i++)
    {
        m_players.push_back(new PlayerManager(i+1));
    }
}

GameManager::~GameManager()
{
    for (PlayerManager* player: m_players)
    {
        delete player;
    }
    if (m_map)
    {
        delete m_map;
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

void GameManager::currentPlayerTurnEnded()
{
    int playerNumber = m_players.size();

    // If last player ended his turn, next turn
    if (m_currentPlayer == playerNumber - 1)
    {
        m_currentPlayer = 0;
        m_currentTurn++;
        emit currentTurnChanged(m_currentTurn);
    }
    else
    {
        m_currentPlayer++;
    }

    emit currentPlayerChanged(m_currentPlayer+1);
}
