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
    connect(ui->endTurnButton, &QPushButton::clicked, this, &UserInterfaceManager::endTurnButtonPushed);

    connect(this, &UserInterfaceManager::endCurrentPlayerTurn,
            m_gameManager, &GameManager::currentPlayerTurnEnded);

    connect(m_gameManager, &GameManager::currentTurnChanged,
            this, &UserInterfaceManager::currentTurnChanged);
    connect(m_gameManager, &GameManager::currentPlayerChanged,
            this, &UserInterfaceManager::currentPlayerChanged);

    connect(m_gameManager, &GameManager::newTileUnit, this, &UserInterfaceManager::displayUnitActions);

    this->show();

    // start the game immediately
    playButtonPushed();
}

UserInterfaceManager::~UserInterfaceManager()
{
    delete ui;
    delete m_gameManager;
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

            m_gameManager->startGame();
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

void UserInterfaceManager::endTurnButtonPushed()
{
    if (isVisibleAndEnabled(ui->endTurnButton))
    {
        emit endCurrentPlayerTurn();
    }
}

void UserInterfaceManager::currentTurnChanged(int turnNumber)
{
    ui->currentTurnLineEdit->setText(QString::number(turnNumber));
}

void UserInterfaceManager::currentPlayerChanged(int playerNumber)
{
    ui->currentPlayerLineEdit->setText(QString::number(playerNumber));
}

void UserInterfaceManager::displayUnitActions(Unit *unit)
{
    clearLayout(ui->unitActions_layout);
    if (unit)
    {
        for (UnitAction action: unit->actions())
        {
            QString actionName = unitActionString(action);
            QPushButton* actionButton = new QPushButton(actionName);
            actionButton->setProperty("actionId", static_cast<int>(action));
            ui->unitActions_layout->addWidget(actionButton);
            connect(actionButton, &QPushButton::clicked, this, &UserInterfaceManager::onActionClicked);
            actionButton->setEnabled(unit->actionAvailable()[action]);
        }
    }
}

//@todo: bug: can move to current tile (wastes MP)
void UserInterfaceManager::onActionClicked()
{
    QPushButton* actionButton = static_cast<QPushButton*>(sender());
    if (actionButton)
    {
        UnitAction action = static_cast<UnitAction>((actionButton->property("actionId").toInt()));

        m_gameManager->executeAction(action);
    }
}

bool UserInterfaceManager::isVisibleAndEnabled(QPushButton* button)
{
    return button->isVisible() && button->isEnabled();
}

// should be move later
void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget())
        {
           delete item->widget();
        }
        delete item;
    }
}

