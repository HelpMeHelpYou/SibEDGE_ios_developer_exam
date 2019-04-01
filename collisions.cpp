#include "collisions.h"
#include <QtGlobal>




bool collisions::isInitCollisions(std::vector<std::vector<CellState> > &field, CellState &future, Pos currentPos)
{
    CellState& previous = field.at(currentPos.X).at(currentPos.Y);
    {
        bool rc  = false;

        if ( future.GetIsGamer() )
        {
            for (unsigned int i = 0 ; i < field.size(); i++)
                for (unsigned int j = 0 ; j < field.size(); j++)


            goto exit;
        }


        if (future.GetIsGamer())
        {
            rc = previous.GetIsBusy();
            goto exit;
        }


        if (future.GetIsGamer())
        {
            rc = previous.GetIsBusy();
            goto exit;
        }

exit:
        return rc;

    }
}

std::vector<Pos> collisions::getNeighbors(const Pos & current,unsigned int fieldSize)
{
    std::vector<Pos> rc;

    if ( current.X >0 )
    {
        Pos newPos = current;
        newPos.X--;
        rc.push_back(newPos);
    }
    if ( current.X <fieldSize-1 )
    {
        Pos newPos = current;
        newPos.X++;
          rc.push_back(newPos);
    }
    if ( current.Y >0 )
    {
        Pos newPos = current;
        newPos.Y--;
          rc.push_back(newPos);
    }
    if ( current.Y < fieldSize-1 )
    {
        Pos newPos = current;
        newPos.X--;
         rc.push_back(newPos);
    }
}

std::vector<Pos> collisions:: getIsTheirWay (std::vector<std::vector<CellState> > & field,
                                             Pos Start,
                                             Pos end,std::vector<bool (CellState::*)(void)> arrayOfCallback )
{
    std::vector <std::vector <unsigned int> > waveField;
    waveField.resize(field.size());
    for ( auto waveArray : waveField)
    {
        waveArray.resize(field.size(),0);
    }

    waveField[Start.X][Start.Y] = 1;

    while (  waveField[end.X][end.Y] == 0)
    {
        for (unsigned int i = 0; i < waveField.size(); i++)
            for (unsigned int j = 0; j < waveField.size(); j++)
            {
                if  (waveField[i][j] > 0)
                {
                    unsigned int value = waveField[i][j];
                Pos current{i,j};
                std::vector<Pos>  vec = getNeighbors(current, waveField.size());
                for (Pos position : vec)
                {
                    if (waveField[position.X][position.Y] == 0 )
                    {
                        bool flag = true;
                        for ( auto callback  : arrayOfCallback)
                        {
                            if  (((field.at(i).at(j)).*callback)())
                            {
                                flag = true;
                                break;
                            }
                        }
                        if (flag)
                        {
                            waveField[position.X][position.Y] = value+1;
                        }
                    }
                }
                }
            }

    }
    return     std::vector<Pos>();
}
