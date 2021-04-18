#ifndef BUILDING_H
#define BUILDING_H

#include <QString>

/*!
 * \brief Stores data of a building.
 */
class Building
{
public:
    Building();

    void investProduction(int production);

    int surplusInvestment();

    int constructionCost() const;
    int productionInvested() const;

    bool isFinished() const;

private:
    QString m_name;
    int m_constructionCost;
    int m_productionInvested;

};

#endif // BUILDING_H
