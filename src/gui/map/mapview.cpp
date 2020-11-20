#include "mapview.h"

#include <QHBoxLayout>
#include "maptile.h"

MapView::MapView(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    m_graphicsView = new QGraphicsView(this);
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
}

void MapView::createScene()
{
    m_scene = new QGraphicsScene(this);
    QImage imageGround(":/image/map_tile/ground.png");
    QImage imageWater(":/image/map_tile/water.png");

    for (int w = 0; w < 10; w++)
    {
        for (int h = 0; h < 10; h++)
        {
            QImage imageToDisplay;
            if ((w+h) < 10)
            {
                imageToDisplay = imageGround;
            }
            else
            {
                imageToDisplay = imageWater;
            }

            MapTile *item = new MapTile(w, h, imageToDisplay);
            item->setPos(item->positionOnMap());
            m_scene->addItem(item);
        }
    }
}

