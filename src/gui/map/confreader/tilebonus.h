#ifndef TILEBONUS_H
#define TILEBONUS_H

#include <QString>

class TileBonus
{
public:
    TileBonus();

    enum class Type
    {
        NONE = 0,
        FOOD = 1,
        PRODUCTION = 2,
        GOLD = 3,
    };

    static TileBonus::Type bonusType(const QString &typeName);
};

#endif // TILEBONUS_H
