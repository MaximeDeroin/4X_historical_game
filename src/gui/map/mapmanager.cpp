#include "mapmanager.h"
#include <QMessageBox>

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
