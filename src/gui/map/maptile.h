#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsObject>
#include "confreader/tileconf.h"
#include "unit/unit.h"

/*!
 * \brief This class manages a tile on the graphical user interface.
 */
class MapTile : public QGraphicsObject//, public QGraphicsItem
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] x Abscissa of the tile.
     * \param[in] y Ordinate of the tile.
     * \param[in] tileConf Tile type configuration.
     */
    explicit MapTile(int x, int y, TileConf* tileConf);

    virtual ~MapTile() = default;

    /*!
     * \brief Adds a modifier(resource) to the tile.
     * \param[in] tileConf Configuration of the modifier.
     */
    void addModifier(TileConf* tileConf);

    Unit *unit() const; //!< Getter of m_unit.

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

    int x() const; //!< Getter of m_x.

    int y() const; //!< Getter of m_y.

    QString backgroundTypeName() const; //!< Returns name of background tile configuration.

    void setSelected(bool selected); //!< Setter of m_selected.

    bool canBeReached() const; //!< Getter of m_canBeReached.
    void setCanBeReached(bool canBeReached); //!< Setter of m_canBeReached.

signals:
    /*!
     * \brief Indicates that the tile has been pressed.
     */
    void tilePressed();

    /*!
     * \brief Indicates that the tile has been released.
     */
    void tileReleased();

    /*!
     * \brief Indicates that the current selected tile contains a unit.
     * \param[in] unit Unit selected.
     */
    void unitSelected(Unit* unit);

    /*!
     * \brief Indicated that the previously selected tile contains a unit.
     * \param[in] unit Unit selected.
     */
    void unitUnselected();

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

    bool m_selected; //!< Indicates if the tile was selected.
    bool m_canBeReached; //!< Indicates if the selected unit can move to this tile.

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
