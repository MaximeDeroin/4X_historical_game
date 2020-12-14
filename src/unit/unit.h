#ifndef UNIT_H
#define UNIT_H

#include <QString>

/*!
 * \brief Stores data of a unit in the game.
 */
class Unit
{
public:
    explicit Unit();

    void setName(const QString &name);

    void setMovementPoints(int movementPoints);

    void setMaxMovementPoints(int maxMovementPoints);

private:
    QString m_name;
    int m_movementPoints;
    int m_maxMovementPoints;
};

#endif // UNIT_H
