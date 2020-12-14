#include "unit.h"

Unit::Unit():
    m_name("Unit"),
    m_movementPoints(1),
    m_maxMovementPoints(1),
    m_image(nullptr)
{

}

void Unit::setName(const QString &name)
{
    m_name = name;
}

void Unit::setMovementPoints(int movementPoints)
{
    m_movementPoints = movementPoints;
}

void Unit::setMaxMovementPoints(int maxMovementPoints)
{
    m_maxMovementPoints = maxMovementPoints;
}

QImage *Unit::image() const
{
    return m_image;
}

void Unit::setImage(QImage *image)
{
    m_image = image;
}

QString Unit::name() const
{
    return m_name;
}
