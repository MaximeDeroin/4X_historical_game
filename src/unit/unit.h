#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QImage>

/*!
 * \brief Stores data of a unit in the game.
 */
class Unit
{
public:
    explicit Unit();

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

private:
    QString m_name; //!< Name of the unit.
    int m_playerNumber; //!< Player number who owns the unit.
    int m_movementPoints; //!< Number of current movement points left.
    int m_maxMovementPoints; //!< Maximum number of movement points.
    QImage* m_image; //!< Image of the unit.
};

#endif // UNIT_H
