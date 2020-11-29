#include "tileconf.h"
#include <QDebug>

TileConf::TileConf(TileConf::Type type, const QString &name, const QString &imageName,
                   const QString &mapAbbreviation,
                   const TileBonuses &tileBonuses, QImage *image):
    m_type(type),
    m_name(name),
    m_imageName(imageName),
    m_mapAbbreviation(mapAbbreviation),
    m_tileBonuses(tileBonuses),
    m_image(image)
{

}

QString TileConf::mapAbbreviation() const
{
    return m_mapAbbreviation;
}

QImage *TileConf::image() const
{
    return m_image;
}