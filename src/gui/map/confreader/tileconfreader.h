#ifndef TILECONFREADER_H
#define TILECONFREADER_H

#include <QVector>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "tileconf.h"

/*!
 * \brief Reads configuration of possible tile types.
 */
class TileConfReader
{
public:
    explicit TileConfReader(); //!< Default constructor.

    /*!
     * \brief Reads the configuration of possible tiles to display in a game map.
     * \param[out] tilesConf Tile configurations for background tiles.
     * \param[out] resourcesConf Tile configurations for resource tiles.
     * \return True is no error was detected.
     */
    static bool ReadAllTileConfigurations(QVector<TileConf *> &tilesConf,
                                   QVector<TileConf *> &resourcesConf);

    QVector<TileConf *> tilesConf() const; //!< Getter of m_tilesConf.

    QVector<TileConf *> resourcesConf() const; //!< Getter of m_resourcesConf.

private:
    /*!
     * \brief Parse a tile type configuration configuration file.
     * \param[in] Tile type configuration configuration file.
     * \return True if the operation worked.
     */
    static bool parseTileConf(TileConf::Type type, QFile *file, TileConf *&tileConf);

    /*!
     * \brief Read the configurations of a certain type and store them in a vector.
     * \param[in] confDir Configuration files directory.
     * \param[out] tileConfs Tile configurations.
     * \param[in] type
     * \return
     */
    static bool readTileConfInFolder(TileConf::Type type, const QDir &confDir, QVector<TileConf *> &tileConfs);

    /*!
     * \brief Reads the next line in the stream and put it in a string.
     * \param[in, out] fileStream Stream containing the tile type configuration file.
     * \param[out] string Stores the line read.
     * \return True if the operation worked.
     */
    static bool readNextString(QTextStream &fileStream, QString& string);

    /*!
     * \brief Reads image of the tile type.
     * \return True if the operation worked.
     */
    static bool readImage(TileConf::Type type, const QString &imageName, QImage *&image);

    /*!
     * \brief Reads the tile type bonuses.
     * \param[in, out] fileStream Stream containing the tile type configuration file.
     * \return True if the operation worked.
     */
    static bool readTileBonuses(QTextStream &fileStream, TileBonuses &tileBonuses);
};

static QString TILES_CONF_FOLDER = "map/tiles"; //!< Folder of background tile type configurations.
static QString RESOURCES_CONF_FOLDER = "map/resources"; //!< Folder of resource type configurations.
static QString TILE_IMAGE_FOLDER = ":/image/map_tile/"; //!< Tile configuration folder.
static QString RESOURCES_IMAGE_FOLDER = ":/image/natural_resources/"; //!< Resource configuration folder.

#endif // TILECONFREADER_H
