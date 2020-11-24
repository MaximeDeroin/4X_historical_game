#include "maptile.h"
#include <QPainter>
#include <QKeyEvent>

MapTile::MapTile(int x, int y, const QImage &tileImage, const QImage &modifierImage):
    m_x(x),
    m_y(y),
    m_tileImage(tileImage),
    m_modifierImage(modifierImage),
    m_selected(false)
{
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF MapTile::boundingRect() const
{
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
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

    if (m_selected)
    {
        double MARGIN = TILESIZE/20;
        QPen pen(Qt::red, TILESIZE/40, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
        painter->setPen(pen);

        painter->drawLine(MARGIN, MARGIN, TILESIZE-MARGIN, MARGIN);
        painter->drawLine(TILESIZE-MARGIN, MARGIN, TILESIZE-MARGIN, TILESIZE-MARGIN);
        painter->drawLine(TILESIZE-MARGIN, TILESIZE-MARGIN, MARGIN, TILESIZE-MARGIN);
        painter->drawLine(MARGIN, TILESIZE-MARGIN, MARGIN, MARGIN);
    }
}

QPointF MapTile::positionOnMap()
{
    return QPointF(m_x*TILE_SIZE, m_y*TILE_SIZE);
}

void MapTile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void MapTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    m_selected = !m_selected;
    update();
}
