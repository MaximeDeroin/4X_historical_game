#ifndef MAPREADER_H
#define MAPREADER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "../maptile.h"
#include "tileconf.h"

class MapReader
{
public:
    MapReader(const QString &filename, bool &success);

    QString error() const;

    QVector<MapTile *> mapTiles() const;

private:
    QString m_mapFilename;
    QString m_mapName;
    int m_mapWidth;
    int m_mapHeight;

    QString m_error;

    QString TILES_CONF_FOLDER = "map/tiles";
    QString RESOURCES_CONF_FOLDER = "map/resources";

    enum class ErrorCode
    {
        EMPTY_FILE = 0,
        GAME_WIDTH_MISSING = 1,
        GAME_HEIGHT_MISSING = 2,
        GAME_WIDTH_NOT_A_NUMBER = 3,
        GAME_HEIGHT_NOT_A_NUMBER = 4,
        TILE_LINE_MISSING = 5,
        RESOURCE_LINE_MISSING = 6,
        TILE_LINE_WRONG_SIZE = 7,
        RESOURCE_LINE_WRONG_SIZE = 8,
        TILE_CONF_ERROR = 9,
        TILE_CONFIGURATION_NOT_FOUND = 10,
        RESOURCE_MAP_TILE_NOT_FOUND = 11,
    };

    QMap<ErrorCode, QString> m_errorDescription;

    QVector<MapTile*> m_mapTiles;

    QVector<TileConf*> m_tilesConf;
    QVector<TileConf*> m_resourcesConf;

    TileConf* findTileConf(QChar abbreviation, TileConf::Type type);

    void parse(QFile *file, bool &success);

    bool readMapParameters(QTextStream &fileStream);
    bool readMapTiles(QTextStream &fileStream);
    bool readMapResources(QTextStream &fileStream);

    bool readTileConf();

    void initErrorDescriptions();
    void addError(ErrorCode error);
    bool descriptionFound(ErrorCode code);
};

#endif // MAPREADER_H
