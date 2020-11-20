#include "maptile.h"
#include <QPainter>

MapTile::MapTile(int x, int y, const QImage &tileImage):
    m_x(x),
    m_y(y),
    m_tileImage(tileImage)
{

}

QRectF MapTile::boundingRect() const
{
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);

//    return QRectF((m_x-1)*TILE_SIZE, (m_y-1)*TILE_SIZE,
//                  m_x*TILE_SIZE, m_y*TILE_SIZE);
}

void MapTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)
    double TILESIZE(static_cast<double>(TILE_SIZE));
    QRectF target(0.0, 0.0, TILESIZE, TILESIZE);
    QRectF source(0.0, 0.0, 100.0, 100.0);

    painter->drawImage(target, m_tileImage, source);
}

QPointF MapTile::positionOnMap()
{
    return QPointF(m_x*TILE_SIZE, m_y*TILE_SIZE);
}
