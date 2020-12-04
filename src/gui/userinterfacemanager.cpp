#include "userinterfacemanager.h"
#include "ui_userinterfacemanager.h"


UserInterfaceManager::UserInterfaceManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInterfaceManager),
    m_gameManager(new GameManager)
{
    ui->setupUi(this);

    ui->infoButton->setDisabled(true);
    connect(ui->playButton, &QPushButton::clicked, this, &UserInterfaceManager::playButtonPushed);
    connect(ui->infoButton, &QPushButton::clicked, this, &UserInterfaceManager::infoButtonPushed);
    connect(ui->quitButton, &QPushButton::clicked, this, &UserInterfaceManager::quitButtonPushed);
    connect(ui->menuButton, &QPushButton::clicked, this, &UserInterfaceManager::menuButtonPushed);

    this->show();
}

UserInterfaceManager::~UserInterfaceManager()
{
    delete ui;
}

int UserInterfaceManager::toInt(UserInterfaceManager::Page page)
{
    return static_cast<int>(page);
}

void UserInterfaceManager::playButtonPushed()
{
    if (isVisibleAndEnabled(ui->playButton))
    {
        QString mapName(":/map/island_1v1.map");

        if(m_gameManager->openMap(mapName))
        {
            ui->gameFrame->loadMap(m_gameManager->mapTiles());
            ui->stackedWidget->setCurrentIndex(toInt(Page::GAME));
        }
    }
}

void UserInterfaceManager::infoButtonPushed()
{
    if (isVisibleAndEnabled(ui->infoButton))
    {

    }
}

void UserInterfaceManager::quitButtonPushed()
{
    if (isVisibleAndEnabled(ui->quitButton))
    {
        qApp->quit();
    }
}

void UserInterfaceManager::menuButtonPushed()
{
    if (isVisibleAndEnabled(ui->menuButton))
    {
        ui->stackedWidget->setCurrentIndex(toInt(Page::MENU));
    }
}

bool UserInterfaceManager::isVisibleAndEnabled(QPushButton* button)
{
    return button->isVisible() && button->isEnabled();
}
