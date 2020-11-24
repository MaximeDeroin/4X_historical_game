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

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void applyZoomLevel();

private:
    MapGraphicsView *m_graphicsView;

    QGraphicsScene *m_scene;

    void createScene();

    int m_zoomLevel;

};

#endif // MAPVIEW_H
