#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsItem>
#include "confreader/tileconf.h"

/*!
 * \brief This class manages a tile on the graphical user interface.
 */
class MapTile : public QGraphicsItem
{
public:
//    MapTile(int x, int y, const QImage &tileImage, const QImage &modifierImage = QImage(0,0));

    /*!
     * \brief Constructor of the class.
     * \param[in] x Abscissa of the tile.
     * \param[in] y Ordinate of the tile.
     * \param[in] tileconf Tile type configuration.
     */
    explicit MapTile(int x, int y, TileConf* tileconf);

    /*!
     * \brief Adds a modifier(resource) to the tile.
     * \param[in] tileConf Configuration of the modifier.
     */
    void addModifier(TileConf* tileConf);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    /*!
     * \brief Returns the tile position on the map.
     * \return Point composed of m_x and m_y.
     */
    QPointF positionOnMap();

protected:
    /*!
     * \brief Triggered when the mouse is pressed on the tile.
     * \param[in] event Event.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /*!
     * \brief Triggered when the mouse is released on the tile.
     * \param[in] event Event.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_x; //!< Abscissa of the tile.
    int m_y; //!< Ordinate of the tile.
    int TILE_SIZE = 200; //!< Size of a tile in pixel.
    QImage* m_tileImage; //!< Image of the background of the tile.
    QImage* m_modifierImage; //!< Image of the tile modifier.
    bool m_selected; //!< indicates if the tile was selected.
};

#endif // MAPTILE_H
