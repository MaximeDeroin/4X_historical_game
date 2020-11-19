#include "userinterfacemanager.h"
#include "ui_userinterfacemanager.h"

UserInterfaceManager::UserInterfaceManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInterfaceManager)
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

void UserInterfaceManager::playButtonPushed()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void UserInterfaceManager::infoButtonPushed()
{

}

void UserInterfaceManager::quitButtonPushed()
{
    qApp->quit();
}

void UserInterfaceManager::menuButtonPushed()
{
    ui->stackedWidget->setCurrentIndex(0);
}
