#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "confreader/mapreader.h"

class MapManager
{
public:
    MapManager();

    bool openMap(const QString &filename);

    QVector<MapTile *> mapTiles() const; //!< Getter of m_mapTiles.

private:

    int m_mapWidth; //!< Width of the map.
    int m_mapHeight; //!< Height of the map.

    QVector<MapTile *> m_mapTiles;
};

#endif // MAPMANAGER_H
