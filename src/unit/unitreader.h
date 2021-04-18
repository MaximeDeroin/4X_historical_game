#ifndef UNITREADER_H
#define UNITREADER_H

#include<QVector>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "unit.h"

/*!
 * \brief This class reads the unit configuration file and creates the Unit instances.
 */
class UnitReader
{
public:
    /*!
     * \brief Constructor of the class.
     */
    explicit UnitReader();

    /*!
     * \brief Read the unit configuration files.
     * \param[out] success True if the configuration read was sucessfull.
     * \return List of configuration files.
     */
    QVector<Unit*> readUnitTypes(bool &success);

private:
    QVector<Unit*> m_unitTypes; //!< List of unit configuration types.

    /*!
     * \brief Parses configuration file and builds the corresponding Unit instance.
     * \param[in] file Configuration file.
     * \param[out] unitConf Unit configuration.
     * \return True is successfull.
     */
    bool parseUnit(QFile *file, Unit *&unitConf);

    /*!
     * \brief Converts a file into a list of lines.
     * \param[in] file File to read
     * \return List of lines of the file.
     */
    QStringList readFileLines(QFile *file);
};

static QString UNIT_IMAGE_FOLDER = ":/image/units/"; //!< Tile configuration folder.


#endif // UNITREADER_H
