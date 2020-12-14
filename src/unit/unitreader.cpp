#include "unitreader.h"
#include <QDebug>

UnitReader::UnitReader()
{

}

QVector<Unit *> UnitReader::readUnitTypes(bool &success)
{
    QDir confDir("../../conf/units/");
    success = true;
    for (const QString& filename: confDir.entryList(QStringList() << "*.yml", QDir::Files))
    {
        QString filepath(confDir.path()+QDir::separator()+filename);
        QFile* file = new QFile(filepath);
        if (!file || !file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "could not open unit file " << filename << "not found";
            success &= false;
        }
        Unit* unit = nullptr;
        if (success)
        {
            success &= parseUnit(file, unit);
        }
        if (success)
        {
            m_unitTypes.push_back(unit);
        }
    }
    return m_unitTypes;
}

bool UnitReader::parseUnit(QFile *file, Unit*& unitConf)
{
    bool success = true;
    QStringList fileLines = readFileLines(file);
    unitConf = new Unit;
    for (QString line: fileLines)
    {
        QStringList lineWords(line.split(":"));
        if (lineWords.size() == 2)
        {
            QString variableName = lineWords.at(0);
            QString variableValue = lineWords.at(1);
            if (variableName == "name")
            {
                unitConf->setName(variableValue);
            }
            else if (variableName == "movement_points")
            {
                bool ok = true;
                int movementPoints = variableValue.toInt(&ok);
                if (ok)
                {
                    unitConf->setMovementPoints(movementPoints);
                    unitConf->setMaxMovementPoints(movementPoints);
                }
            }
            else if (variableName == "action")
            {
            // else add action
            }
        }
    }

    return success;
}


QStringList UnitReader::readFileLines(QFile *file)
{
    QTextStream fileStream(file);
    QStringList fileLines;
    while (!fileStream.atEnd())
    {
        fileLines << fileStream.readLine();
    }
    return fileLines;
}
