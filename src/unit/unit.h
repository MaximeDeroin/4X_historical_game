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

private:
    QString m_name;
    int m_movementPoints;
    int m_maxMovementPoints;
    QImage* m_image; //!< Image of the unit.
};

#endif // UNIT_H
