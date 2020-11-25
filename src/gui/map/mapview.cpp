#include "mapview.h"

#include <QHBoxLayout>
#include "maptile.h"
#include "confreader/mapreader.h"
#include <qmath.h>
#include <QMessageBox>

MapView::MapView(QWidget *parent)
    : QFrame(parent)
{
    m_zoomLevel = DEFAULT_ZOOM_LEVEL;
    setFrameStyle(Sunken | StyledPanel);
    m_graphicsView = new MapGraphicsView(this);
    m_graphicsView->setRenderHint(QPainter::Antialiasing, false);
    m_graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    m_graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->createScene();
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

void MapView::createScene()
{
    m_scene = new QGraphicsScene(this);

    bool mapReadSucessfully = true;
//    MapReader reader(":/map/map1.map", mapReadSucessfully);
    MapReader reader(":/map/island.map", mapReadSucessfully);

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
    /*
    QImage imageGround(":/image/map_tile/ground.png");
    QImage imageWater(":/image/map_tile/water.png");
    QImage imageStone(":/image/natural_resources/stone.png");
    QImage imageCow(":/image/natural_resources/cow.png");
    for (int w = 0; w < 10; w++)
    {
        for (int h = 0; h < 10; h++)
        {
            QImage imageToDisplay;
            QImage resourcesImage(0,0);
            if ((w+h) < 10)
            {
                imageToDisplay = imageGround;
                if (w+h == w*w)
                {
                    resourcesImage = imageStone;
                }
                else if (h*h == w+h)
                {
                    resourcesImage = imageCow;
                }
            }
            else
            {
                imageToDisplay = imageWater;
            }

            MapTile *item = new MapTile(w, h, imageToDisplay, resourcesImage);
            item->setPos(item->positionOnMap());
            m_scene->addItem(item);
        }
    }*/
}


MapGraphicsView::MapGraphicsView(MapView *view):
    m_view(view)
{

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
