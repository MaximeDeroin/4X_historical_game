#ifndef UNITACTION_H
#define UNITACTION_H

#include <QString>

/*!
 * \brief Enumeration of unit special actions.
 */
enum class UnitAction
{
    SETTLE = 1,
};

/*!
 * \brief String to display for a unit action.
 * \param[in] action Unit action.
 * \return String to display for a unit action.
 */
QString unitActionString(UnitAction action);

#endif // UNITACTION_H
