#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "playermanager.h"
#include "../gui/map/mapmanager.h"

/*!
 * \brief Stores the information of a game.
 */
class GameManager: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor of the class.
     * \param[in] playerNumber Number of player in the game.
     * \param[in] parent Parent object.
     */
    explicit GameManager(int playerNumber = 3, QObject *parent = nullptr);

    virtual ~GameManager(); //!< Default destructor.

    /*!
     * \brief Opens and parses the map file.
     * \param[in] filename Name of the map file.
     * \return True if successfull.
     */
    bool openMap(const QString &filename);

    QVector<MapTile *> mapTiles() const; //!< Getter of m_mapTiles.

    /*!
     * \brief Initializes and starts the game.
     */
    void startGame();

signals:
    /*!
     * \brief Indicates a change of turn.
     * \param[in] turnNumber New turn number.
     */
    void currentTurnChanged(int turnNumber);

    /*!
     * \brief Indicates a change of player.
     * \param[in] playerNumber New player number.
     */
    void currentPlayerChanged(int PlayerNumber);

public slots:
    /*!
     * \brief Manages an end of turn.
     */
    void currentPlayerTurnEnded();

private:
    int MIN_PLAYER = 1; //!< Minimum number of player.
    int MAX_PLAYER = 10; //!< Maximum number of player.
    int m_currentTurn; //!< Turn number.

    int m_currentPlayer; //!< Index of the current player.

    QVector<PlayerManager*> m_players; //!< List of players.
    QVector<Unit*> m_possibleUnits; //!< List of possible units.

    QMap<QString, Unit*> m_unitsByName; //!< Dictionnary of units by name.

    MapManager* m_map; //!< Map manager.
};

#endif // GAMEMANAGER_H
