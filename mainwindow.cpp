#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_gameinitializationparamsi.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::pressed,this,&MainWindow::onPushButtonNewGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModel(QAbstractItemModel *model)
{
    ui->tableView->setModel(model);
}

void MainWindow::OnUpdateGameState(GameState newState)
{
    QString str;
    switch(newState)
    {
        case GameState::noGame:
        str = QObject::tr("No Game");
        break;

    case GameState::activeGame:
    str = QObject::tr("active game");
    break;

    case GameState::failedGame:
    str = QObject::tr("failed game");
    break;

    case GameState::victoriedGame:
    str = QObject::tr("victory");
    QMessageBox box (this);
    box.setText(QObject::tr("victory!"));
    box.exec();
    break;

    }
    ui->groupBox->setTitle(str);
    ui->labelGameStatus->setText(str);
}

void MainWindow::onPushButtonNewGame()
{
    QDialog dialog;
    Ui::Dialog d;
    d.setupUi(&dialog);
    d.spinBoxChamberSize->setValue(GameinitializationParams::defualtChamberSize);
    d.spinBoxGoldNumber->setValue(GameinitializationParams::defualtGoldNumber);
    d.spinBoxHolesNumber->setValue(GameinitializationParams::defualtHolesNumer);
    d.spinBoxGoldNumber->setValue(GameinitializationParams::defualtRobotsNumber);

    dialog.exec();

    if (dialog.result() == QDialog::Accepted)
    {
        GameinitializationParams params;
        params.chamberSize = static_cast<unsigned int> (d.spinBoxChamberSize->value());
        params.goldNumber =  static_cast<unsigned int> (d.spinBoxGoldNumber->value());
        params.robotsNumber = static_cast<unsigned int> (d.spinBoxRobotNumber->value());
        params.holesNumer = static_cast<unsigned int> (d.spinBoxHolesNumber->value());

        emit NewGame (params);
    }
}



void MainWindow::on_actionExit_triggered()
{
    emit exit();
}

void MainWindow::on_pushButtonRight_released()
{
    newAction(Action::moveRight);
}

void MainWindow::on_pushButtonUp_released()
{
    newAction(Action::moveUp);
}

void MainWindow::on_pushButtonDown_released()
{
    newAction(Action::moveDown);
}

void MainWindow::on_pushButtonLeft_released()
{
    newAction(Action::moveLeft);
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_pushButtonExit_clicked()
{
    emit exit();
}
