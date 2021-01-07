#include "mapmanager.h"
#include <QMessageBox>
#include <ctime>

MapManager::MapManager():
    m_currentlySelectedTile(nullptr),
    m_mapTiles()
{

}

bool MapManager::openMap(const QString &filename)
{
    bool mapReadSucessfully = true;
    MapReader reader(filename, mapReadSucessfully);

    if (mapReadSucessfully)
    {
        m_mapTiles = reader.mapTiles();
        this->connectMapTiles();

        m_mapWidth = reader.mapWidth();
        m_mapHeight = reader.mapHeight();
    }
    else
    {
        QMessageBox messageBox("Error reading map", reader.error(),QMessageBox::Icon::Critical, 0,0,0);
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }
    return mapReadSucessfully;
}

void MapManager::connectMapTiles()
{
    for (MapTile* tile: m_mapTiles)
    {
        connect(tile, &MapTile::tilePressed, this, &MapManager::onTilePressed);
        connect(tile, &MapTile::tileReleased, this, &MapManager::onTileReleased);

        connect(tile, &MapTile::unitSelected, this, &MapManager::onUnitSelected);
        connect(tile, &MapTile::unitUnselected, this, &MapManager::onUnitUnselected);
    }
}

QVector<MapTile *> MapManager::mapTiles() const
{
    return m_mapTiles;
}

QVector<MapTile *> MapManager::selectStartingPoints(int playerNumber)
{
    std::srand(std::time(0));
    QVector<MapTile *> candidateTiles = potentialStartingTiles();
    QVector<MapTile *> selectedTiles;
    int tryNumber = 0;
    int tryLimit = candidateTiles.size()*10;

    while (selectedTiles.size() != playerNumber && tryNumber < tryLimit)
    {
        int randomIndex = std::rand() % candidateTiles.size();
        MapTile* candidate = candidateTiles.at(randomIndex);
        if (selectedTiles.size() == 0)
        {
            selectedTiles.push_back(candidate);
        }
        else
        {
            bool distanceOK = true;
            for (MapTile* selectedTile: selectedTiles)
            {
                if (distance(candidate, selectedTile) <= 6)
                {
                    distanceOK = false;
                    break;
                }
            }
            if (distanceOK)
            {
                selectedTiles.push_back(candidate);
            }
        }
        tryNumber++;
    }
    return selectedTiles;
}

int MapManager::distance(MapTile *first, MapTile *second)
{
    if (!first || !second)
    {
        return -1;
    }

    return abs(first->x() - second->x()) + abs(first->y() - second->y());
}

QVector<MapTile *> MapManager::potentialStartingTiles()
{
    QVector<MapTile *> potentialStartingTiles;
    QVector<QString> nonStartingTileTypes{"Water"};
    for (MapTile* tile: m_mapTiles)
    {
        if (!nonStartingTileTypes.contains(tile->backgroundTypeName()))
        {
            potentialStartingTiles.push_back(tile);
        }
    }
    return potentialStartingTiles;
}

void MapManager::onTilePressed()
{
    m_currentTilePressed = dynamic_cast<MapTile*>(sender());
}

void MapManager::onTileReleased()
{
    MapTile* releasedTile = dynamic_cast<MapTile*>(sender());
    if (releasedTile != nullptr && releasedTile == m_currentTilePressed)
    {
        if (m_currentlySelectedTile && (m_currentlySelectedTile == releasedTile))
        {
            m_currentlySelectedTile->setSelected(false);
            m_currentlySelectedTile = nullptr;
        }
        else
        {
            if (m_currentlySelectedTile)
            {
                m_currentlySelectedTile->setSelected(false);
            }
            m_currentlySelectedTile = releasedTile;
            releasedTile->setSelected(true);
        }
    }
}

void MapManager::onUnitSelected(Unit *unit)
{
    int movementPoints = unit->movementPoints();
    if (movementPoints > 0)
    {
        MapTile* selectedTile = static_cast<MapTile*>(sender());
        int x = selectedTile->x();
        int y = selectedTile->y();
        setNeighborsCanBeReached(x, y , true);
    }
}

void MapManager::onUnitUnselected()
{
    MapTile* selectedTile = static_cast<MapTile*>(sender());
    int x = selectedTile->x();
    int y = selectedTile->y();
    setNeighborsCanBeReached(x, y , false);
}

void MapManager::setNeighborsCanBeReached(int x, int y, bool canBeReached)
{
    setCanBeReached(x-1, y-1, canBeReached);
    setCanBeReached(x-1, y, canBeReached);
    setCanBeReached(x-1, y+1, canBeReached);
    setCanBeReached(x, y-1, canBeReached);
    setCanBeReached(x, y+1, canBeReached);
    setCanBeReached(x+1, y-1, canBeReached);
    setCanBeReached(x+1, y, canBeReached);
    setCanBeReached(x+1, y+1, canBeReached);
}

void MapManager::setCanBeReached(int x, int y, bool canBeReached)
{
    if (isInMap(x,y))
    {
        m_mapTiles.at(y*m_mapWidth+x)->setCanBeReached(canBeReached);
    }
}

bool MapManager::isInMap(int x, int y)
{
    return ((x >= 0) && (y >= 0) && (x < m_mapWidth) && (y < m_mapHeight));
}
