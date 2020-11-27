#ifndef TILEBONUS_H
#define TILEBONUS_H

#include <QString>

/*!
 * \brief Manages the type of bonus that a game tile can provide.
 */
class TileBonus
{
public:
    /*!
     * \brief Default constructor of the class.
     */
    TileBonus();

    /*!
     * \brief Possible type of bonus of a game tile.
     */
    enum class Type
    {
        NONE = 0,
        FOOD = 1,
        PRODUCTION = 2,
        GOLD = 3,
    };

    /*!
     * \brief Returns the type of tile bonus in function of its name in the tile configuration file.
     * \param[in] typeName Name of the type of bonus in the map file.
     * \return Type of tile bonus.
     */
    static TileBonus::Type bonusType(const QString &typeName);
};

#endif // TILEBONUS_H
