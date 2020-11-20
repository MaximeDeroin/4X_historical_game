#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QFrame>
#include <QGraphicsItem>
#include <QGraphicsView>

class MapView : public QFrame
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = nullptr);

private:
    QGraphicsView *m_graphicsView;

    QGraphicsScene *m_scene;

    void createScene();

};

#endif // MAPVIEW_H
