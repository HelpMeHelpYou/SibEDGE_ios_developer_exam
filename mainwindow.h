#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>

#include "gameinitializationparams.h"
#include "action.h"
#include "gamestate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setModel (QAbstractItemModel *model);

public Q_SLOTS:
    void OnUpdateGameState (GameState newState);

Q_SIGNALS:
    void NewGame (GameinitializationParams);
    void exit (void);
    void newAction (Action);

private:
    Ui::MainWindow *ui;

private Q_SLOTS:
        void onPushButtonNewGame (void);
        void on_actionExit_triggered();
        void on_pushButtonRight_released();
        void on_pushButtonUp_released();
        void on_pushButtonDown_released();
        void on_pushButtonLeft_released();
        void on_actionAbout_triggered();
        void on_pushButtonExit_clicked();
};

#endif // MAINWINDOW_H
