#ifndef USERINTERFACEMANAGER_H
#define USERINTERFACEMANAGER_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class UserInterfaceManager;
}

/*!
 * \brief Manages the Graphical µUser Interface of the game.
 * UI file describes the GUI layout.
 */
class UserInterfaceManager : public QWidget
{
    Q_OBJECT

private:
    /*!
     * \brief Enumerates the different pages(screens) of the game gui.
     */
    enum class Page
    {
        MENU = 0,
        GAME = 1
    };

    /*!
     * \brief Converts page enumeration value to and integer.
     * \param[in] page Page enumeration  value.
     * \return Page enumeration value casted as an integer.
     */
    int toInt(Page page);

public:
    /*!
     * \brief Constructor of the class.
     * \param[in] parent Parent object.
     */
    explicit UserInterfaceManager(QWidget *parent = 0);

    ~UserInterfaceManager(); //!< Default destructor.

private slots:
    /*!
     * \brief Manages a push on the "Play" button.
     * \todo If no game currently, create new game, else load current game.
     */
    void playButtonPushed();

    /*!
     * \brief Manages a push on the "Info" button.
     */
    void infoButtonPushed();

    /*!
     * \brief Manages a push on the "Quit" button.
     */
    void quitButtonPushed();

    /*!
     * \brief Manages a push on the "Menu" button.
     */
    void menuButtonPushed();

private:
    Ui::UserInterfaceManager *ui; //!< GUI description.

    /*!
     * \brief Indicates if a QPushbutton instance is enabled and visible.
     * \param[in] button QPushButton instance.
     * \return True if QPushbutton instance is enabled and visible.
     */
    bool isVisibleAndEnabled(QPushButton *button);
};

#endif // USERINTERFACEMANAGER_H
