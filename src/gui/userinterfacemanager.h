#ifndef USERINTERFACEMANAGER_H
#define USERINTERFACEMANAGER_H

#include <QWidget>

namespace Ui {
class UserInterfaceManager;
}

class UserInterfaceManager : public QWidget
{
    Q_OBJECT

private:
    enum class Page
    {
        MENU = 0,
        GAME = 1
    };

    int toInt(Page page);

public:
    explicit UserInterfaceManager(QWidget *parent = 0);
    ~UserInterfaceManager();

private slots:
    void playButtonPushed();
    void infoButtonPushed();
    void quitButtonPushed();
    void menuButtonPushed();

private:
    Ui::UserInterfaceManager *ui;
};

#endif // USERINTERFACEMANAGER_H
