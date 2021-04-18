#ifndef TILECONF_H
#define TILECONF_H
#include <QString>
#include <QMap>
#include <QImage>
#include "tilebonus.h"

//typedef QPair<TileBonus::Type, int> BonusValue;
//typedef QVector<BonusValue> TileBonuses;
typedef QMap<TileBonus::Type, int> TileBonuses;

/*!
 * \brief Stores the information of a tile configuration.
 */
class TileConf
{
public:
    /*!
     * \brief Tile category: background or resource.
     */
    enum class Type
    {
        TILE = 0,
        NATURAL_RESOURCE = 1
    };
    /*!
     * \brief Constructor of the class.
     * \param[in] type Tile category.
     * \param[in] name Name of the tile type.
     * \param[in] imageName Name of the image file.
     * \param[in] mapAbbreviation Abbreviation of the tile type.
     * \param[in] tileBonuses Bonuses of the tile.
     * \param[in] image Image of the tile.
     */
    explicit TileConf(TileConf::Type type, const QString& name, const QString& imageName,
                      const QString& mapAbbreviation,
                      const TileBonuses& tileBonuses, QImage* image);

    ~TileConf(); //!< Destructor of the class.

    QString mapAbbreviation() const; //!< Getter of m_mapAbbreviation.

    QImage *image() const; //!< Getter of m_image.

    QString name() const; //!< Getter of m_name.

    TileBonuses tileBonuses() const; //!< Getter of m_tileBonuses.

    bool isGround(); //!< Indicates if the tile is a ground tile.

private:
    TileConf::Type m_type; //!< Tile category.

    QString m_name; //!< Name of the tile type.
    QString m_imageName; //!< Name of the image file.
    QString m_mapAbbreviation; //!< Abbreviation of the tile type.
    TileBonuses m_tileBonuses; //!< Bonuses of the tile.

    QImage* m_image; //!< Image of the tile.
};

#endif // TILECONF_H
