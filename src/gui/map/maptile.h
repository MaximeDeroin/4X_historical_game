#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsItem>
#include "confreader/tileconf.h"
#include "unit/unit.h"

/*!
 * \brief This class manages a tile on the graphical user interface.
 */
class MapTile : public QGraphicsItem
{
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] x Abscissa of the tile.
     * \param[in] y Ordinate of the tile.
     * \param[in] tileConf Tile type configuration.
     */
    explicit MapTile(int x, int y, TileConf* tileConf);

    /*!
     * \brief Adds a modifier(resource) to the tile.
     * \param[in] tileConf Configuration of the modifier.
     */
    void addModifier(TileConf* tileConf);

    /*!
     * \brief Sets a unit to the tile.
     * \param[in] unit Instance of the unit.
     */
    void setUnit(Unit* unit);

    /*!
     * \brief Gives bounds of the tile, relative to the tile position on the view.
     * \return Bounds of the tile.
     */
    QRectF boundingRect() const override;

    /*!
     * \brief Explains how the tile should be painted on screen.
     * \param[in] painter Painter for the tile?
     * \param[in] item Unused. Needed for ovverride.
     * \param[in] widget Unused. Needed for ovverride.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    /*!
     * \brief Returns the tile position on the map.
     * \return Point composed of m_x and m_y.
     */
    QPointF positionOnMap();

    int x() const;

    int y() const;

    QString backgroundTypeName() const;

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

    /*!
     * \brief Add bonuses to the current instance.
     * \param[in] bonusesToAdd Bonuses to add.
     */
    void addTileBonuses(const TileBonuses& bonusesToAdd);

private:
    int m_x; //!< Abscissa of the tile.
    int m_y; //!< Ordinate of the tile.
    int TILE_SIZE = 200; //!< Size of a tile in pixel.
    QImage* m_tileImage; //!< Image of the background of the tile.
    QImage* m_modifierImage; //!< Image of the tile modifier.
    bool m_selected; //!< indicates if the tile was selected.

    TileConf* m_backgroundTileConf; //!< Configuration of the background.
    TileConf* m_modifierTileConf; //!< Configuration of the modifier.
    Unit* m_unit; //!< Configuration of the unit.
    TileBonuses m_tileBonuses; //!< Tile bonuses.

    /*!
     * \brief Updates the message to display when the player hovers over the tile.
     */
    void updateToolTip();
};

#endif // MAPTILE_H
