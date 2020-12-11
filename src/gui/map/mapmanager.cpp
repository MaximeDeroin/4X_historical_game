#include "mapmanager.h"
#include <QMessageBox>
#include <ctime>

MapManager::MapManager():
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
