#include "unitaction.h"

QString unitActionString(UnitAction action)
{
    switch(action){
        case UnitAction::SETTLE:
            return "Create a city";
        default:
            return "Unknown unit action";
    }
}
