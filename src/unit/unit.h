#ifndef UNIT_H
#define UNIT_H

#include <QImage>
#include <QMap>
#include "unitaction.h"

/*!
 * \brief Stores data of a unit in the game.
 */
class Unit
{
public:
    explicit Unit(); //!< Constructor of the class.

    ~Unit(); //!< Destructor of the class.

    QString name() const;  //!< Getter of m_name.
    void setName(const QString &name); //!< Setter of m_name.

    int movementPoints() const; //!< Getter of m_movementPoints.
    void setMovementPoints(int movementPoints); //!< Setter of m_movementPoints.

    int maxMovementPoints() const; //!< Getter of m_maxMovementPoints.
    void setMaxMovementPoints(int maxMovementPoints); //!< Setter of m_maxMovementPoints.

    QImage *image() const; //!< Getter of m_image.
    void setImage(QImage *image); //!< Setter of m_image.

    int playerNumber() const; //!< Getter of m_playerNumber.
    void setPlayerNumber(int playerNumber); //!< Setter of m_playerNumber.

    QColor playerColor() const; //!< Getter of m_playerColor.
    void setPlayerColor(const QColor &playerColor); //!< Setter of m_playerColor.

    void resetMovementPoints(); //!< Resets movement points to the maximum.

    void addAction(UnitAction action); //!< Adds an action to the unit class.

    QVector<UnitAction> actions() const; //!< List of actions doable by the unit.

    QMap<UnitAction, bool> actionAvailable() const; //!< Indicates for each action if it is available

private:
    QString m_name; //!< Name of the unit.
    int m_playerNumber; //!< Player number who owns the unit.
    QColor m_playerColor; //!< Player color.
    int m_movementPoints; //!< Number of current movement points left.
    int m_maxMovementPoints; //!< Maximum number of movement points.
    QImage* m_image; //!< Image of the unit.

    QVector<UnitAction> m_unitActions; //!< List of actions doable by the unit.
    QMap<UnitAction, bool> m_actionAvailable; //!< Indicates for each action if it is available
};

#endif // UNIT_H
