#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <vector>

#include <QAbstractTableModel>

#include "gamestate.h"
#include "cellstate.h"
#include "gameinitializationparams.h"
#include "action.h"

class GameStateMachine : public QAbstractTableModel
{
    Q_OBJECT
public:
    GameStateMachine();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void checkFailed(const CellState &newCell);

public Q_SLOTS:
    void NewGame (GameinitializationParams);
    void NewAction (Action);

Q_SIGNALS:
    void StateUpdated(GameState);

private:
    GameState _state = GameState::noGame;
    unsigned int _chamberSize = 0;
    unsigned int _goldCounter =0;

    std::vector<std::vector<CellState>> _field;

    void swapGamer(CellState& oldCell, CellState& newCell);

    void checkVictory();
};

#endif // GAMESTATEMACHINE_H
