#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "playermanager.h"

/*!
 * \brief Stores the information of a game.
 */
class GameManager
{
public:
    explicit GameManager(int playerNumber = 1);

private:
    int m_currentTurn; //!< Turn number.

    QVector<PlayerManager*> m_players; //!< List of players.
};

#endif // GAMEMANAGER_H
