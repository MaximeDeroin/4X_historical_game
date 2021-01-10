#include "maptile.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

MapTile::MapTile(int x, int y, TileConf *tileConf):
    m_x(x),
    m_y(y),
    m_tileImage(tileConf->image()),
    m_modifierImage(nullptr),
    m_selected(false),
    m_canBeReached(false),
    m_backgroundTileConf(tileConf),
    m_modifierTileConf(nullptr),
    m_unit(nullptr),
    m_tileBonuses()
{
    addTileBonuses(tileConf->tileBonuses());

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setFocus(Qt::MouseFocusReason);
    this->updateToolTip();
}

void MapTile::addModifier(TileConf *tileConf)
{
    m_modifierImage = tileConf->image();
    addTileBonuses(tileConf->tileBonuses());
    m_modifierTileConf = tileConf;
    this->updateToolTip();
}

void MapTile::setUnit(Unit *unit)
{
    m_unit = unit;
    this->updateToolTip();
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
    QRectF targetUnit(TILESIZE/4, TILESIZE/4, TILESIZE/2, TILESIZE/2);

    if (m_tileImage)
    {
        QRectF sourceTile(0.0, 0.0, m_tileImage->size().width(),  m_tileImage->size().height());

        painter->drawImage(target, *m_tileImage, sourceTile);
    }

    if (m_modifierImage)
    {
        QRectF sourceModifier(0.0, 0.0, m_modifierImage->size().width(),  m_modifierImage->size().height());
        if (m_modifierImage->size() != QSize(0,0))
            painter->drawImage(target, *m_modifierImage, sourceModifier);
    }

    if (m_unit && m_unit->image())
    {
        QImage* unitImage = m_unit->image();
        QRectF sourceModifier(0.0, 0.0, unitImage->size().width(),  unitImage->size().height());
        if (unitImage->size() != QSize(0,0))
            painter->drawImage(targetUnit, *unitImage, sourceModifier);
    }

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

    if (m_canBeReached)
    {
        double MARGIN = TILESIZE/20;
        QPen pen(Qt::darkRed, TILESIZE/40, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
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
    //qDebug() << m_x << ", " << m_y << "pressed ";
    //QGraphicsItem::mousePressEvent(event);
    update();
    emit tilePressed();
}

void MapTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << m_x << ", " << m_y << "released ";
    //QGraphicsItem::mouseReleaseEvent(event);
//    m_selected = !m_selected;
    update();
    emit tileReleased();
}

void MapTile::addTileBonuses(const TileBonuses &bonusesToAdd)
{
    for (TileBonus::Type type: bonusesToAdd.keys())
    {
        bool typeAlreadyPresent = m_tileBonuses.keys().contains(type);

        if (typeAlreadyPresent)
        {
            m_tileBonuses[type] += bonusesToAdd[type];
        }
        else
        {
            m_tileBonuses[type] = bonusesToAdd[type];
        }
    }
}

Unit *MapTile::unit() const
{
    return m_unit;
}

bool MapTile::canBeReached() const
{
    return m_canBeReached;
}

void MapTile::setCanBeReached(bool canBeReached)
{
    m_canBeReached = canBeReached;
    update();
}

QString MapTile::backgroundTypeName() const
{
    return m_backgroundTileConf->name();
}

void MapTile::setSelected(bool selected)
{
    m_selected = selected;
    if (selected && m_unit)
    {
        emit unitSelected(m_unit);
    }
    else if (!selected && m_unit)
    {
        emit unitUnselected();
    }
    update();
}

int MapTile::y() const
{
    return m_y;
}

int MapTile::x() const
{
    return m_x;
}

void MapTile::updateToolTip()
{
    QString toolTip;

    if (m_backgroundTileConf)
    {
        toolTip += m_backgroundTileConf->name();
    }

    if (m_modifierTileConf && m_modifierTileConf->name() != "None")
    {
        toolTip += "\n";
        toolTip +=m_modifierTileConf->name();
    }

    for (TileBonus::Type type: m_tileBonuses.keys())
    {
        toolTip += "\n";
        toolTip += QString("%1 : %2").arg(TileBonus::bonusName(type))
                                     .arg(m_tileBonuses[type]);
    }

    if (m_unit)
    {
        toolTip += "\n";
        toolTip += QString("%1 (player %2): %3/%4 MP").arg(m_unit->name())
                                            .arg(m_unit->playerNumber())
                                            .arg(m_unit->movementPoints())
                                            .arg(m_unit->maxMovementPoints());
    }

    setToolTip(toolTip);
}
