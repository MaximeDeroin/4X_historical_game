#include "conffilereader.h"

ConfFileReader::ConfFileReader()
{

}

StringPairs ConfFileReader::parseConfFile(QFile *file, bool& ok)
{
    StringPairs result;
    QStringList fileLines = ConfFileReader::readFileLines(file);

    for (const QString& line: fileLines)
    {
        QStringList lineWords(line.split(":"));
        if (lineWords.size() == 2)
        {
            result.push_back(std::move(StringPair(lineWords.at(0), lineWords.at(1))));
        }
        else
        {
            ok &= false;
        }
    }
    return result;
}


QStringList ConfFileReader::readFileLines(QFile *file)
{
    QTextStream fileStream(file);
    QStringList fileLines;
    while (!fileStream.atEnd())
    {
        fileLines << fileStream.readLine();
    }
    return fileLines;
}
