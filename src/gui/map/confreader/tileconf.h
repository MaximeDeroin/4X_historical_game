#ifndef TILECONF_H
#define TILECONF_H
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include "tilebonus.h"

/*!
 * \brief Stores the information of a tile configuration.
 * \todo Split in 2 classes. New class TileConfReader reads and fills an object TileConf
 */
class TileConf
{
public:
    /*!
     * \brief Tile category: background ot resource.
     */
    enum class Type
    {
        TILE = 0,
        NATURAL_RESOURCE = 1
    };

    /*!
     * \brief Constructor of teh class.
     * \param[in] filename Name of the tile configuration file.
     * \param[in] type Tile category.
     * \param[out] creationOK Indicates if the creation of the object has of failed.
     */
    explicit TileConf(const QString &filename, TileConf::Type type, bool &creationOK);

    QString TILE_IMAGE_FOLDER = ":/image/map_tile/"; //!< Tile configuration folder.
    QString RESOURCES_IMAGE_FOLDER = ":/image/natural_resources/"; //!< Resource configuration folder.

    QString mapAbbreviation() const; //!< Getter of m_mapAbbreviation.

    QImage *image() const; //!< Getter of m_image.

private:
    TileConf::Type m_type; //!< Tile category.

    QString m_name; //!< Name of the tile type.
    QString m_imageName; //!< Name of the image file.
    QString m_mapAbbreviation; //!< Abbreviation of the tile type.
    QVector<QPair<TileBonus::Type, int>> m_tileBonuses; //!< Bonuses of the tile.

    QImage* m_image; //!< Image of the tile.

    /*!
     * \brief Parse a tile type configuration configuration file.
     * \param[in] Tile type configuration configuration file.
     * \return True if the operation worked.
     */
    bool parse(QFile *file);

    /*!
     * \brief Reads the next line in the stream and put it in a string.
     * \param[in, out] fileStream Stream containing the tile type configuration file.
     * \param[out] string Stores the line read.
     * \return True if the operation worked.
     */
    bool readNextString(QTextStream &fileStream, QString& string);

    /*!
     * \brief Reads image of the tile type.
     * \return True if the operation worked.
     */
    bool readImage();

    /*!
     * \brief Reads the tile type bonuses.
     * \param[in, out] fileStream Stream containing the tile type configuration file.
     * \return True if the operation worked.
     */
    bool readTileBonuses(QTextStream &fileStream);
};

#endif // TILECONF_H
