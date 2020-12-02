#include "mapview.h"

#include <QHBoxLayout>
#include "maptile.h"
#include "confreader/mapreader.h"
#include <qmath.h>
#include <QMessageBox>
#include <QDebug>

MapView::MapView(QWidget *parent)
    : QFrame(parent)
{
    m_zoomLevel = DEFAULT_ZOOM_LEVEL;
    setFrameStyle(Sunken | StyledPanel);
    m_graphicsView = new MapGraphicsView(this);
    m_graphicsView->initializeParameters();
}

void MapView::loadMap(const QString& mapName)
{
    this->createScene(mapName);
    m_graphicsView->setScene(m_scene);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_graphicsView, 0, 0);
    setLayout(topLayout);
    this->applyZoomLevel();

}

void MapView::applyZoomLevel()
{
    qreal scale = qPow(qreal(2), (m_zoomLevel - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);

    m_graphicsView->setMatrix(matrix);
}

void MapView::createScene(const QString& mapName)
{
    m_scene = new QGraphicsScene(this);
    bool mapReadSucessfully = true;
//    MapReader reader(":/map/map1.map", mapReadSucessfully);
    MapReader reader(mapName, mapReadSucessfully);

    if (mapReadSucessfully)
    {
        for (MapTile* tile: reader.mapTiles())
        {
            tile->setPos(tile->positionOnMap());
            m_scene->addItem(tile);
        }
    }
    else
    {
        QMessageBox messageBox("Error reading map", reader.error(),QMessageBox::Icon::Critical, 0,0,0);
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }
}


MapGraphicsView::MapGraphicsView(MapView *view):
    m_view(view)
{
}

void MapGraphicsView::initializeParameters()
{
    this->setRenderHint(QPainter::Antialiasing, false);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setDragMode(QGraphicsView::RubberBandDrag);
//    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setInteractive(true);
}

void MapGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        m_view->zoomIn(6);
    }
    else
    {
        m_view->zoomOut(6);
    }
    event->accept();
}

void MapView::zoomIn(int level)
{
    if (m_zoomLevel <= MAX_ZOOM_LEVEL)
    {
        m_zoomLevel += level;
    }
    this->applyZoomLevel();
}

void MapView::zoomOut(int level)
{
    if (m_zoomLevel >= MIN_ZOOM_LEVEL)
    {
        m_zoomLevel -= level;
    }
    this->applyZoomLevel();
}
