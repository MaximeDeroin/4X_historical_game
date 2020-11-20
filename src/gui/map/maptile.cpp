#include "maptile.h"
#include <QPainter>

MapTile::MapTile(int x, int y, const QImage &tileImage, const QImage &modifierImage):
    m_x(x),
    m_y(y),
    m_tileImage(tileImage),
    m_modifierImage(modifierImage)
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
    QRectF sourceTile(0.0, 0.0, m_tileImage.size().width(),  m_tileImage.size().height());
    QRectF sourceModifier(0.0, 0.0, m_modifierImage.size().width(),  m_modifierImage.size().height());

    painter->drawImage(target, m_tileImage, sourceTile);
    if (m_modifierImage.size() != QSize(0,0))
        painter->drawImage(target, m_modifierImage, sourceModifier);
}

QPointF MapTile::positionOnMap()
{
    return QPointF(m_x*TILE_SIZE, m_y*TILE_SIZE);
}
