#include "tileconfreader.h"
#include <QDebug>

TileConfReader::TileConfReader()
{

}

bool TileConfReader::readAllTileConfigurations(QVector<TileConf*> &tilesConf,
                                               QVector<TileConf*> &resourcesConf)
{
    QDir confFolder("../../conf/");
    QDir tilesConfDir(confFolder.path()+QDir::separator()+TILES_CONF_FOLDER);
    QDir resourcesConfDir(confFolder.path()+QDir::separator()+RESOURCES_CONF_FOLDER);

    qDebug() << "tile conf: " << tilesConfDir.absolutePath();

    bool success = true;

    success &= readTileConfInFolder(TileConf::Type::TILE, tilesConfDir, tilesConf);

    success &= readTileConfInFolder(TileConf::Type::NATURAL_RESOURCE, resourcesConfDir, resourcesConf);

    return success;
}

bool TileConfReader::readTileConfInFolder(TileConf::Type type, const QDir &confDir, QVector<TileConf *> &tileConfs)
{
    bool success = true;
    for (const QString& filename: confDir.entryList(QStringList() << "*.conf", QDir::Files))
    {
        QString filepath(confDir.path()+QDir::separator()+filename);
        qDebug() << "found tile conf: " << filepath;

        QFile* file = new QFile(filepath);
        if (!file || !file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "could not open file " << filename << "not found";
            success &= false;
        }
        if (success)
        {
            TileConf* tileConf = nullptr;
            success &= parseTileConf(type, file, tileConf);
            if (success)
                tileConfs.push_back(tileConf);
        }
    }
    return success;
}

bool TileConfReader::parseTileConf(TileConf::Type type, QFile *file, TileConf*& tileConf)
{
    bool success = true;
    QTextStream fileStream(file);
    QString name;
    QString imageName;
    QString mapAbbreviation;
    TileBonuses tileBonuses;

    QImage* image = nullptr;

    if (!fileStream.atEnd())
    {
        success &= readNextString(fileStream, name);
        success &= readNextString(fileStream, imageName);
        success &= readNextString(fileStream, mapAbbreviation);

        success &= readImage(type, imageName, image);
        success &= readTileBonuses(fileStream, tileBonuses);
    }
    else
    {
        success = false;
    }

    if (success)
    {
        tileConf = new TileConf(type, name, imageName, mapAbbreviation, tileBonuses, image);
    }
    return success;
}

bool TileConfReader::readNextString(QTextStream &fileStream, QString& string)
{
    if (fileStream.atEnd())
        return false;

    string = fileStream.readLine();

    return !string.isEmpty();
}

bool TileConfReader::readImage(TileConf::Type type, const QString &imageName, QImage*& image)
{
    if (imageName == "none")
    {
        image = nullptr;
        return true;
    }

    QString folder;
    switch (type)
    {
    case TileConf::Type::TILE:
        folder = TILE_IMAGE_FOLDER;
        break;
    case TileConf::Type::NATURAL_RESOURCE:
        folder = RESOURCES_IMAGE_FOLDER;
        break;
    default:
        break;
    }

    QString imagePath(folder+imageName);
    image = new QImage(imagePath);

    return (image != nullptr);
}

bool TileConfReader::readTileBonuses(QTextStream &fileStream, TileBonuses &tileBonuses)
{
    QVector<QString> remainingLines;

    while (!fileStream.atEnd())
    {
        QString newLine = fileStream.readLine();
        if (!newLine.isEmpty())
        {
            remainingLines.push_back(newLine);
        }
    }

    // check that the remaining line number is even to be able
    // to create pairs
    if (remainingLines.size()%2 != 0)
    {
        return false;
    }
    for (int i=0; i<remainingLines.size(); i+=2)
    {
        QString bonusName = remainingLines.at(i);
        QString bonusValue = remainingLines.at(i+1);

        TileBonus::Type bonusType = TileBonus::bonusType(bonusName);
        if (bonusType == TileBonus::Type::NONE)
        {
            return false;
        }

        bool ok = true;
        int value = bonusValue.toInt(&ok);
        if (!ok)
        {
            return false;
        }

        tileBonuses[bonusType] = value;
        //        tileBonuses.push_back(BonusValue(bonusType, value));
    }

    return true;
}
