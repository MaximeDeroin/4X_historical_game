#include "gamemanager.h"
#include <QDebug>
#include "unit/unitreader.h"

GameManager::GameManager(int playerNumber, QObject *parent):
    QObject(parent),
    m_currentTurn(0),
    m_currentPlayer(0),
    m_possibleUnits(),
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

    UnitReader reader;
    bool ok = true;
    m_possibleUnits = reader.readUnitTypes(ok);
    for(Unit* unit: m_possibleUnits)
    {
        m_unitsByName[unit->name()] = unit;
    }

    connect(m_map, &MapManager::requestMoveUnit, this, &GameManager::onRequestMoveUnit);
}

GameManager::~GameManager()
{
    for (PlayerManager* player: m_players)
    {
        delete player;
    }

    for (Unit* unit: m_possibleUnits)
    {
        delete unit;
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

void GameManager::startGame()
{
    QVector<MapTile*> startingPoints = m_map->selectStartingPoints(m_players.size());

    for (MapTile* tile: startingPoints)
    {
        qDebug() << "tile position: (" << tile->x() << ", " << tile->y() << ")";
    }
    if (startingPoints.size() != m_players.size())
    {
        qDebug() << startingPoints.size() << "!=" << m_players.size();
        return;
    }

    for (int i=0; i<m_players.size(); i++)
    {
        //m_players.at(i)->setStartingPosition(startingPoints.at(i));
        m_players.at(i)->addUnit(m_unitsByName["Settler"], startingPoints.at(i));
    }

}

void GameManager::currentPlayerTurnEnded()
{
    int playerNumber = m_players.size();

    m_players[m_currentPlayer]->processEndTurnEvents();

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

    m_players[m_currentPlayer]->processBeginTurnEvents();

    emit currentPlayerChanged(m_currentPlayer+1);
}

void GameManager::onRequestMoveUnit(MapTile *origin, MapTile *destination)
{
    if (!origin || !destination || !(origin->unit()))
    {
        qDebug() << "invalid move unit requested";
        return;
    }
    if (destination->unit() != nullptr)
    {
        return;
    }
    Unit* unit = origin->unit();
    if (unit->playerNumber() == m_currentPlayer+1)
    {
        m_map->moveUnit(origin, destination);
    }
}
