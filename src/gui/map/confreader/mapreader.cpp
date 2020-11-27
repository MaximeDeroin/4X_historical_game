#include "mapreader.h"
#include <QDebug>
#include <QDir>

MapReader::MapReader(const QString &filename, bool &success):
    m_mapFilename(filename),
    m_mapName(),
    m_mapWidth(0),
    m_mapHeight(0),
    m_error(),
    m_mapTiles(QVector<MapTile*>())
{
    success = true;
    success &= this->readTileConf();

    this->initErrorDescriptions();
    QFile* file = new QFile(filename);
    if (!file || !file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QDir::currentPath();
        qDebug() << "file " << filename << "not found";
        return;
    }
    parse(file, success);
}

QString MapReader::error() const
{
    return m_error;
}

QVector<MapTile *> MapReader::mapTiles() const
{
    return m_mapTiles;
}

TileConf *MapReader::findTileConf(const QChar& abbreviation, TileConf::Type type)
{
    QString abbr(abbreviation);
    QVector<TileConf*> confList;
    if (type == TileConf::Type::TILE)
    {
        confList = m_tilesConf;
    }
    else if (type == TileConf::Type::NATURAL_RESOURCE)
    {
        confList = m_resourcesConf;
    }
    else
    {
        addError(ErrorCode::TILE_CONF_ERROR);
        return nullptr;
    }

    for (TileConf* tileConf: confList)
    {
        if(tileConf->mapAbbreviation() == abbr)
        {
            return tileConf;
        }
    }

    addError(ErrorCode::TILE_CONFIGURATION_NOT_FOUND);
    return nullptr;
}

bool MapReader::readMapParameters(QTextStream &fileStream)
{
    // Read map name
    m_mapName = fileStream.readLine();
    bool isInt = true;

    // Read map width
    if (fileStream.atEnd())
    {
        addError(ErrorCode::GAME_WIDTH_MISSING);
    }
    else
    {
        QString mapWidth = fileStream.readLine();

        m_mapWidth = mapWidth.toInt(&isInt);
        if (!isInt)
        {
            addError(ErrorCode::GAME_WIDTH_NOT_A_NUMBER);
        }
    }

    // Read map height
    if (fileStream.atEnd())
    {
        addError(ErrorCode::GAME_HEIGHT_MISSING);
    }
    else
    {
        QString mapHeight = fileStream.readLine();

        m_mapHeight = mapHeight.toInt(&isInt);
        if (!isInt)
        {
            addError(ErrorCode::GAME_HEIGHT_NOT_A_NUMBER);
        }
    }

    return m_error.isEmpty();
}

bool MapReader::readMapTiles(QTextStream &fileStream)
{
    QVector<QString> tileLines;

    for (int h=0; h < m_mapHeight; h++)
    {
        QString newLine(fileStream.readLine());
        // allow to skip lines
        while (newLine.isEmpty() && !fileStream.atEnd())
        {
            newLine = fileStream.readLine();
        }

        if (newLine.isEmpty() && fileStream.atEnd())
        {
            addError(ErrorCode::TILE_LINE_MISSING);
            break;
        }

        tileLines.push_back(newLine);
    }

    int h=0;
    for (const QString &line: tileLines)
    {
        if (line.size() != m_mapWidth)
        {
            addError(ErrorCode::TILE_LINE_WRONG_SIZE);
            break;
        }
        int w = 0;
        for (QChar c: line)
        {
            TileConf* tileConf = findTileConf(c, TileConf::Type::TILE);
            if (tileConf)
            {
                MapTile* mapTile = new MapTile(w, h, tileConf);
                m_mapTiles.push_back(mapTile);
            }
            w++;
        }
        h++;
    }
    qDebug() << m_error;
    return m_error.isEmpty();
}

bool MapReader::readMapResources(QTextStream &fileStream)
{
    QVector<QString> resourceLines;

    for (int h=0; h < m_mapHeight; h++)
    {
        QString newLine(fileStream.readLine());
        // allow to skip lines
        while (newLine.isEmpty() && !fileStream.atEnd())
        {
            newLine = fileStream.readLine();
        }

        if (newLine.isEmpty() && fileStream.atEnd())
        {
            addError(ErrorCode::RESOURCE_LINE_MISSING);
            break;
        }

        resourceLines.push_back(newLine);
    }

    int h=0;
    for (const QString &line: resourceLines)
    {
        if (line.size() != m_mapWidth)
        {
            addError(ErrorCode::RESOURCE_LINE_WRONG_SIZE);
            break;
        }
        int w = 0;
        for (QChar c: line)
        {
            TileConf* resourceConf = findTileConf(c, TileConf::Type::NATURAL_RESOURCE);
            int index = h*m_mapWidth+w;

            if (index < m_mapTiles.size())
            {
                if (resourceConf)
                {
                    MapTile* mapTile = m_mapTiles.at(index);
                    mapTile->addModifier(resourceConf);
                }
            }
            else
            {
                addError(ErrorCode::RESOURCE_MAP_TILE_NOT_FOUND);
            }
            w++;
        }
        h++;
    }

    return m_error.isEmpty();
}

bool MapReader::readTileConf()
{
    QDir confFolder("../../conf/");
    QDir tilesConfDir(confFolder.path()+QDir::separator()+TILES_CONF_FOLDER);
    QDir resourcesConfDir(confFolder.path()+QDir::separator()+RESOURCES_CONF_FOLDER);

    qDebug() << "tile conf: " << tilesConfDir.absolutePath();

    bool success = true;

    for (const QString& file: tilesConfDir.entryList(QStringList() << "*.conf", QDir::Files))
    {
        bool ok = true;
        QString filepath(tilesConfDir.path()+QDir::separator()+file);
        qDebug() << "found tile conf: " << filepath;
        TileConf* tileConf = new TileConf(filepath, TileConf::Type::TILE, ok);
        success &= ok;
        if (ok)
            m_tilesConf.push_back(tileConf);
    }

    for (const QString& file: resourcesConfDir.entryList(QStringList() << "*.conf", QDir::Files))
    {
        bool ok = true;
        QString filepath(resourcesConfDir.path()+QDir::separator()+file);
        qDebug() << "found resource conf: " << filepath;
        TileConf* tileConf = new TileConf(filepath, TileConf::Type::NATURAL_RESOURCE, ok);
        success &= ok;
        if (ok)
            m_resourcesConf.push_back(tileConf);
    }
    return success;
}

void MapReader::initErrorDescriptions()
{
    m_errorDescription.insert(ErrorCode::EMPTY_FILE,
                              QString("The map file %1 is empty.").arg(m_mapFilename));
    m_errorDescription.insert(ErrorCode::GAME_HEIGHT_MISSING,
                              QString("Error in %1: map height not found").arg(m_mapFilename));
    m_errorDescription.insert(ErrorCode::GAME_HEIGHT_NOT_A_NUMBER,
                              QString("Error in %1: map height not an integer").arg(m_mapFilename));
    m_errorDescription.insert(ErrorCode::GAME_WIDTH_MISSING,
                              QString("Error in %1: map width not found").arg(m_mapFilename));
    m_errorDescription.insert(ErrorCode::GAME_WIDTH_NOT_A_NUMBER,
                              QString("Error in %1: map width not an integer").arg(m_mapFilename));
    m_errorDescription.insert(ErrorCode::TILE_LINE_MISSING,
                              QString("Error in %1: Missing tile line").arg(m_mapFilename));
    m_errorDescription.insert(ErrorCode::RESOURCE_LINE_MISSING,
                              QString("Error in %1: Missing resource line").arg(m_mapFilename));
}

void MapReader::addError(MapReader::ErrorCode error)
{
    if (descriptionFound(error))
    {
        m_error += m_errorDescription[error];
    }
    else
    {
        m_error += QString("Error reading %1, error code: %2")
                .arg(m_mapFilename)
                .arg(static_cast<int>(error));
    }
    m_error += "\n";
}

bool MapReader::descriptionFound(MapReader::ErrorCode code)
{
    return (m_errorDescription.find(code) != m_errorDescription.end());
}

void MapReader::parse(QFile *file, bool &success)
{
    QTextStream fileStream(file);

    if (!fileStream.atEnd())
    {
        success = readMapParameters(fileStream);
    }
    else
    {
        success = false;
    }

    if (success)
    {
        success = readMapTiles(fileStream);
    }

    if (success)
    {
        success = readMapResources(fileStream);
    }
}
