#ifndef TILECONF_H
#define TILECONF_H
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include "tilebonus.h"

class TileConf
{
public:
    
    enum class Type
    {
        TILE = 0,
        NATURAL_RESOURCE = 1
    };
    TileConf(const QString &filename, TileConf::Type type, bool &creationOK);

    QString TILE_IMAGE_FOLDER = ":/image/map_tile/";
    QString RESOURCES_IMAGE_FOLDER = ":/image/natural_resources/";

    QString mapAbbreviation() const;

    QImage *image() const;

private:
    TileConf::Type m_type;

    QString m_name;
    QString m_imageName;
    QString m_mapAbbreviation;
    QVector<QPair<TileBonus::Type, int>> m_tileBonuses;

    QImage* m_image;

    bool parse(QFile *file);

    bool readNextString(QTextStream &fileStream, QString& string);

    bool readImage();

    bool readTileBonuses(QTextStream &fileStream);

};

#endif // TILECONF_H
