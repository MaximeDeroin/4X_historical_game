#include "gamemanager.h"

GameManager::GameManager(int playerNumber):
    m_currentTurn(0)
{
    for (int i = 0; i<playerNumber; i++)
    {
        m_players.push_back(new PlayerManager);
    }
}
