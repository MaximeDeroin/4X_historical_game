#include "tilebonus.h"

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
