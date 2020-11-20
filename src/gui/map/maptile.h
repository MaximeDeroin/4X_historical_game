#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsItem>

class MapTile : public QGraphicsItem
{
public:
    MapTile(int x, int y, const QImage &tileImage, const QImage &modifierImage = QImage(0,0));

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QPointF positionOnMap();

private:
    int m_x;
    int m_y;
    int TILE_SIZE = 200;
    QImage m_tileImage;
    QImage m_modifierImage;
};

#endif // MAPTILE_H
