#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QFrame>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QWheelEvent>

class MapView;
/*!
 * \brief Override of QGraphicsView to add zoom with mouse wheel button.
 */
class MapGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] view Associated MapView instance.
     */
    explicit MapGraphicsView(MapView *view);

    /*!
     * \brief Triggered when mouse wheel button is activated. Changes zoom level.
     * \param[in] event Event.
     */
    void wheelEvent(QWheelEvent *event) override;

    /*!
     * \brief Initializes graphics view parameters.
     */
    void initializeParameters();
private:
    MapView *m_view; //!< View associated with the class.
};


/*!
 * \brief Manages the game view in the graphical user interface.
 */
class MapView : public QFrame
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] parent Parent object.
     */
    explicit MapView(QWidget *parent = nullptr);

    /*!
     * \brief Load a map file and display the game.
     * \param[in] mapName Name of the map file.
     */
    void loadMap(const QString &mapName);

public slots:
    /*!
     * \brief Increases the zoom level.
     * \param[in] level Change in zoom level.
     */
    void zoomIn(int level = 1);

    /*!
     * \brief Decreases the zoom level.
     * \param[in] level Change in zoom level.
     */
    void zoomOut(int level = 1);

private slots:
    /*!
     * \brief Updates view with the current zoom level.
     */
    void applyZoomLevel();

private:
    MapGraphicsView *m_graphicsView; //!< Scene container.

    QGraphicsScene *m_scene; //!< Scene, contains individual elements of the game view.

    int m_zoomLevel; //!< Current zoom level.

    int DEFAULT_ZOOM_LEVEL = 180; //!< Default zoom level.
    int MIN_ZOOM_LEVEL = 140; //!< Lower limit for zoom level.
    int MAX_ZOOM_LEVEL = 280; //!< Upper limit for zoom level.

    /*!
     * \brief Creates the scene with elements described in the map file.
     * \param[in] mapName Name of the map file.
     * \todo move map loading in loadMap (MapReader instanciation)
     */
    void createScene(const QString &mapName);
};

#endif // MAPVIEW_H
