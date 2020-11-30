#include "tilebonus.h"
#include <QObject>

TileBonus::TileBonus()
{

}

TileBonus::Type TileBonus::bonusType(const QString &typeName)
{
    if (typeName == "food")
        return TileBonus::Type::FOOD;
    if (typeName == "prod")
        return TileBonus::Type::PRODUCTION;
    if (typeName == "gold")
        return TileBonus::Type::GOLD;

    return TileBonus::Type::NONE;
}

QString TileBonus::bonusName(TileBonus::Type bonusType)
{
    switch(bonusType)
    {
    case TileBonus::Type::FOOD:
        return QString(QObject::tr("Food"));
        break;
    case TileBonus::Type::PRODUCTION:
        return QString(QObject::tr("Production"));
        break;
    case TileBonus::Type::GOLD:
        return QString(QObject::tr("Gold"));
        break;
    default:
        return "Undefined bonus";
        break;
    }
}
