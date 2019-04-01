#include "mainwindow.h"
#include "gamestatemachine.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    GameStateMachine game;
    w.setModel(&game);

    QObject::connect (&w,&MainWindow::NewGame,&game,&GameStateMachine::NewGame);
    QObject::connect (&w,&MainWindow::exit,&a,&QApplication::quit);
    QObject::connect (&w,&MainWindow::newAction,&game,&GameStateMachine::NewAction);

    QObject::connect (&game,&GameStateMachine::StateUpdated,&w,&MainWindow::OnUpdateGameState);

    return a.exec();
}
