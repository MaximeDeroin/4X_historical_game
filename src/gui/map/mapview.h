#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QFrame>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QWheelEvent>

class MapView;
class MapGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MapGraphicsView(MapView *view);

    void wheelEvent(QWheelEvent *event) override;

private:
    MapView *m_view;
};


class MapView : public QFrame
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = nullptr);

    void loadMap(const QString &mapName);
public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void applyZoomLevel();

private:
    MapGraphicsView *m_graphicsView;

    QGraphicsScene *m_scene;

    void createScene(const QString &mapName);

    int m_zoomLevel;

    int DEFAULT_ZOOM_LEVEL = 180;
    int MIN_ZOOM_LEVEL = 140;
    int MAX_ZOOM_LEVEL = 280;

};

#endif // MAPVIEW_H
