#include "gamestatemachine.h"

#include <functional>

#include <QDebug>
#include <QFont>
#include <QBrush>

GameStateMachine::GameStateMachine()
{

}

int GameStateMachine::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return static_cast<int> (_chamberSize);
}

int GameStateMachine::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return static_cast<int> (_chamberSize);
}

QVariant GameStateMachine::data(const QModelIndex &index, int role) const
{
    unsigned int row = static_cast<unsigned int>(index.row());
    unsigned int col = static_cast<unsigned int>(index.column());
    // generate a log message when this method gets called



    qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);

    switch (role) {
    case Qt::DisplayRole:
    {
        QString str;
        if(_field.at(col).at(row).GetIsGold())
        {
            str += QObject::tr("G");
        }
        if(_field.at(col).at(row).GetIsGamer())
        {
            str += QObject::tr("Y");
        }
        if(_field.at(col).at(row).GetIsRobot())
        {
            str += QObject::tr("R");
        }
        if(_field.at(col).at(row).GetIsHoles())
        {
            str += QObject::tr("H");
        }
        return str;
    }

    case Qt::FontRole:
        if (_field.at(col).at(row).GetIsGamer()) { //change font only for cell(0,0)
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;
    case Qt::BackgroundRole:
    {
        QString str;
        QColor color = Qt::white;
        if(_field.at(col).at(row).GetIsGold())
        {
            color = Qt::yellow;
        }
        if(_field.at(col).at(row).GetIsGamer())
        {
            color = Qt::cyan;
        }
        if(_field.at(col).at(row).GetIsRobot())
        {
            color = Qt::red;

        }
        if(_field.at(col).at(row).GetIsHoles())
        {
            color = Qt::gray;
        }

        return QBrush(color);
    }
    case Qt::TextAlignmentRole:
        return Qt::AlignRight + Qt::AlignLeft;

    case Qt::CheckStateRole:

        break;
    }
    return QVariant();
}

void GameStateMachine::NewGame(GameinitializationParams params)
{
    beginResetModel();
    _chamberSize = params.chamberSize;

    unsigned int failCount = 10;

    for ( ; failCount>0;)
    {
        _field.clear();
        _goldCounter = 0;

        _field.resize(_chamberSize);
        for ( std::vector<CellState> & vec: _field)
        {
            vec.resize(_chamberSize);
        }

        unsigned int gamerPosition =  ( static_cast<unsigned int>(qrand()) % (_chamberSize*_chamberSize));

        _field.at(gamerPosition/_chamberSize).at(gamerPosition%_chamberSize).SetIsGamer(true);

        auto f = [&]( void (CellState::*func)(bool), unsigned int paramCount) -> unsigned int{
            unsigned int result =0;
            for (unsigned int i = 0; i < paramCount; i++){
                unsigned int currentPosition =  ( static_cast<unsigned int>(qrand()) % (_chamberSize*_chamberSize));

                for (unsigned int i = 0 ;  ;i++,currentPosition++)
                {
                    currentPosition = currentPosition % (_chamberSize*_chamberSize);
                    CellState & state =_field.at(currentPosition/_chamberSize).at(currentPosition%_chamberSize);
                    if (!state.GetIsBusy())
                    {
                        (state.*func)(true);
                        result++;
                        break;
                    }
                    if (i >= (_chamberSize*_chamberSize))
                    {
                        return false;
                    }
                }
            }
            return result;
        };

        if( !( params.robotsNumber == f(&CellState::SetIsRobot,params.robotsNumber) &&
               params.goldNumber ==(_goldCounter = f(&CellState::SetIsGold,params.goldNumber)) &&
              params.holesNumer == f(&CellState::SetIsHoles,params.holesNumer)))
        {
            failCount--;
        }
        else {
            break;
        }


    }
    this->_state =  GameState::activeGame;
      emit StateUpdated(GameState::activeGame);
    endResetModel();
}

void GameStateMachine::checkVictory()
{
    if (!_goldCounter)
    {
        this->_state = GameState::victoriedGame;
        emit StateUpdated(GameState::victoriedGame);
    }
}

void GameStateMachine::checkFailed(const CellState& newCell)
{
    /*
        CellState* rightCell =  &oldCell;
        CellState* leftCell =  &oldCell;
        CellState* upCell =  &oldCell;
        CellState* downCell =  &oldCell;

        if (gamerPosX>0)
        {
            rightCell = &_field[gamerPosX-1][gamerPosY];
            swapGamer(oldCell,*newCell);
        }

        if (gamerPosX<_field.size()-1)
        {
            leftCell = &_field[gamerPosX+1][gamerPosY];
        }

        if (gamerPosY>0)
        {
            upCell = &_field[gamerPosX][gamerPosY-1];
        }


        if (gamerPosY<_field.size()-1)
        {
            downCell = &_field[gamerPosX][gamerPosY+1];
        }
        if (rightCell->GetIsRobot() ||
                leftCell->GetIsRobot() ||
                upCell->GetIsRobot() ||
                downCell->GetIsRobot())
        {
            this->_state = GameState::failedGame;
            emit StateUpdated(GameState::failedGame);
        }

    */
    if (newCell.GetIsRobot())
    {
        this->_state = GameState::failedGame;
        emit StateUpdated(GameState::failedGame);
    }
}

void GameStateMachine::NewAction(Action act)
{
    beginResetModel();
    if (this->_state !=  GameState::activeGame)
        return;
    unsigned int gamerPosX =0,gamerPosY=0;
    for (unsigned int k = 0 ; k < _field.size() ; k++)
    {
        for (unsigned int i = 0 ; i < _field.size() ; i++)
        {
            if (_field.at(k).at(i).GetIsGamer())
            {
                gamerPosX = k;
                gamerPosY = i;
                goto out_of_cycle;
            }
        }
    }

out_of_cycle:

    CellState& oldCell  = _field[gamerPosX][gamerPosY];
    CellState* newCell = &oldCell;


    switch (act)
    {
    case Action::moveRight:
        if (gamerPosX>0)
        {
            newCell = &_field[gamerPosX-1][gamerPosY];
            swapGamer(oldCell,*newCell);
        }
        break;

    case Action::moveLeft:
        if (gamerPosX<_field.size()-1)
        {
            newCell = &_field[gamerPosX+1][gamerPosY];
            swapGamer(oldCell,*newCell);
        }
        break;

    case Action::moveUp:
        if (gamerPosY>0)
        {
            newCell = &_field[gamerPosX][gamerPosY-1];
            swapGamer(oldCell,*newCell);
        }
        break;

    case Action::moveDown:
        if (gamerPosY<_field.size()-1)
        {
            newCell = &_field[gamerPosX][gamerPosY+1];
            swapGamer(oldCell,*newCell);
        }
        break;

    }

    checkVictory();

    checkFailed(*newCell);

    endResetModel();
}

void GameStateMachine::swapGamer(CellState &oldCell, CellState &newCell)
{
    if (!newCell.GetIsHoles() && !newCell.GetIsRobot())
    {
        oldCell.SetIsGamer(false);
        newCell.SetIsGamer(true);
        if (newCell.GetIsGold())
        {
            _goldCounter--;
            newCell.SetIsGold(false);
        }
    }
}
