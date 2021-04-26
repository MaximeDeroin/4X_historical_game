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

    StringPairs confValues = ConfFileReader::parseConfFile(file, success);

    //QStringList fileLines = ConfFileReader::readFileLines(file);
    unitConf = new Unit;

    for (const StringPair& confValue: confValues) {

        QString variableName = confValue.first;
        QString variableValue = confValue.second;

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
        else if (variableName == "image_name")
        {
            QString imagePath(UNIT_IMAGE_FOLDER+variableValue);
            unitConf->setImage(new QImage(imagePath));
        }
        else if (variableName == "action")
        {
            if (variableValue == "settle")
            {
                unitConf->addAction(UnitAction::SETTLE);
            }
        }
    }

    return success;
}

