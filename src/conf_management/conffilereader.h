#ifndef CONFFILEREADER_H
#define CONFFILEREADER_H

#include <QVector>
#include <QFile>
#include <QDir>
#include <QTextStream>

typedef QPair<QString,QString> StringPair;
typedef QVector<StringPair> StringPairs;

/*!
 * \brief Basic classes to read yml configuration files.
 */
class ConfFileReader
{
public:
    /*!
     * \brief Constructor of the class.
     */
    explicit ConfFileReader();

    /*!
     * \brief Reads a configuration file and return a (name,value) list of attributes.
     * \param[in] file File to read.
     * \param[in] ok True if the file was read successfully.
     * \return List of (name,value) pairs of yml attributes.
     */
    static StringPairs parseConfFile(QFile *file, bool& ok);

private:
    /*!
     * \brief Converts a file into a list of lines.
     * \param[in] file File to read
     * \return List of lines of the file.
     */
    static QStringList readFileLines(QFile *file);
};

#endif // CONFFILEREADER_H
