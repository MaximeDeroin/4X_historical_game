#include "tileconf.h"
#include <QDebug>
typedef QPair<TileBonus::Type, int> BonusValue;

TileConf::TileConf(const QString &filename, TileConf::Type type, bool &creationOK):
    m_type(type),
    m_name(),
    m_imageName(),
    m_mapAbbreviation(),
    m_image(nullptr)
{
    QFile* file = new QFile(filename);
    if (!file || !file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "could not open file " << filename << "not found";
        creationOK = false;
        return;
    }

    creationOK = this->parse(file);

}

bool TileConf::parse(QFile *file)
{
    bool success = true;
    QTextStream fileStream(file);
    if (!fileStream.atEnd())
    {
        success &= readNextString(fileStream, m_name);
        success &= readNextString(fileStream, m_imageName);
        success &= readNextString(fileStream, m_mapAbbreviation);

        success &= readImage();
        success &= readTileBonuses(fileStream);
    }
    else
    {
        success = false;
    }
    return success;
}

bool TileConf::readNextString(QTextStream &fileStream, QString& string)
{
    if (fileStream.atEnd())
        return false;

    string = fileStream.readLine();

    return !string.isEmpty();
}

bool TileConf::readImage()
{
    if (m_imageName == "none")
    {
        m_image = nullptr;
        return true;
    }

    QString folder;
    switch (m_type)
    {
    case TileConf::Type::TILE:
        folder = TILE_IMAGE_FOLDER;
        break;
    case TileConf::Type::NATURAL_RESOURCE:
        folder = RESOURCES_IMAGE_FOLDER;
        break;
    default:
        break;
    }

    QString imagePath(folder+m_imageName);
    m_image = new QImage(imagePath);

    return (m_image != nullptr);
}

bool TileConf::readTileBonuses(QTextStream &fileStream)
{
    QVector<QString> remainingLines;

    while (!fileStream.atEnd())
    {
        QString newLine = fileStream.readLine();
        if (!newLine.isEmpty())
        {
            remainingLines.push_back(newLine);
        }
    }

    // check that the remaining line number is even to be able
    // to create pairs
    if (remainingLines.size()%2 != 0)
    {
        return false;
    }
    for (int i=0; i<remainingLines.size(); i+=2)
    {
        QString bonusName = remainingLines.at(i);
        QString bonusValue = remainingLines.at(i+1);

        TileBonus::Type bonusType = TileBonus::bonusType(bonusName);
        if (bonusType == TileBonus::Type::NONE)
        {
            return false;
        }

        bool ok = true;
        int value = bonusValue.toInt(&ok);
        if (!ok)
        {
            return false;
        }

        m_tileBonuses.push_back(BonusValue(bonusType, value));
    }

    return true;
}

QString TileConf::mapAbbreviation() const
{
    return m_mapAbbreviation;
}

QImage *TileConf::image() const
{
    return m_image;
}
