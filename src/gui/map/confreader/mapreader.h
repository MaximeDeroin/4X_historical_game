#ifndef MAPREADER_H
#define MAPREADER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "../maptile.h"
#include "tileconfreader.h"

/*!
 * \brief This class reads a game map file and builds the corresponding tile configuration.
 * The tile configuration of the map is stored in m_mapTiles (public getter mapTiles()).
 */
class MapReader
{
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] filename Name of the map file.
     * \param[out] success Indicates if the map was read successfully.
     */
    MapReader(const QString &filename, bool &success);

    /*!
     * \brief Errors encountered whhile reading the map file.
     * Empty if no error.
     * \return List of errors in a string.
     */
    QString error() const;

    QVector<MapTile *> mapTiles() const; //!< Getter of m_mapTiles.

private:
    QString m_mapFilename; //!< Name of the map file.
    QString m_mapName; //!< Name of the map.
    int m_mapWidth; //!< Width of the map.
    int m_mapHeight; //!< Height of the map.

    QString m_error; //!< Errors encountered while reading the map file.

    enum class ErrorCode //!< Possible error codes.
    {
        EMPTY_FILE = 0,
        GAME_WIDTH_MISSING = 1,
        GAME_HEIGHT_MISSING = 2,
        GAME_WIDTH_NOT_A_NUMBER = 3,
        GAME_HEIGHT_NOT_A_NUMBER = 4,
        TILE_LINE_MISSING = 5,
        RESOURCE_LINE_MISSING = 6,
        TILE_LINE_WRONG_SIZE = 7,
        RESOURCE_LINE_WRONG_SIZE = 8,
        TILE_CONF_ERROR = 9,
        TILE_CONFIGURATION_NOT_FOUND = 10,
        RESOURCE_MAP_TILE_NOT_FOUND = 11,
    };

    QMap<ErrorCode, QString> m_errorDescription; //!< Description of each of the errors.

    QVector<MapTile*> m_mapTiles; //!< Map tile configuration.

    QVector<TileConf*> m_tilesConf; //!< Tile type configurations for background tiles.
    QVector<TileConf*> m_resourcesConf; //!< Tile type configurations for resource tiles.

    /*!
     * \brief Find the tile type configuration for a given tile abbreviation.
     * \param[in] abbreviation Tile abbreviation.
     * \param[in] type Tile type.
     * \return Tile type configuration.
     */
    TileConf* findTileConf(const QChar& abbreviation, TileConf::Type type);

    void parse(QFile *file, bool &success);

    /*!
     * \brief Reads the first part of the map file containing the map parameters.
     * \param[in, out] fileStream File stream containing the map file.
     * \return True if the operation has not failed.
     */
    bool readMapParameters(QTextStream &fileStream);

    /*!
     * \brief Reads the part of the map file containing the background tile description.
     * \param[in, out] fileStream File stream containing the map file.
     * \return True if the operation has not failed.
     */
    bool readMapTiles(QTextStream &fileStream);

    /*!
     * \brief Reads the part of the map file describing the presence and type of
     * resource for each tile.
     * \param[in, out] fileStream File stream containing the map file.
     * \return True if the operation has not failed.
     */
    bool readMapResources(QTextStream &fileStream);

    /*!
     * \brief Fills m_errorDescription with error descriptions.
     */
    void initErrorDescriptions();

    /*!
     * \brief Adds the error to the error list m_error.
     * \param[in] error Error code.
     */
    void addError(ErrorCode error);

    /*!
     * \brief Indicates if the error code has a description.
     * \param [in] code Error code.
     * \return True if the the error code has a description.
     */
    bool descriptionFound(ErrorCode code);
};

#endif // MAPREADER_H
