#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>

#include "cellstate.h"

struct Pos
{
    Pos (unsigned int x , unsigned y)
    {
        X = x;
        Y = y;
    }
    unsigned int X;
    unsigned int Y;
};

class collisions
{
public:
    static bool isInitCollisions(std::vector<std::vector<CellState> > & field,
                          CellState& future,
                          Pos currentPos);

    static bool gameCollisions(CellState& previous,CellState& future,unsigned int currentPosX,unsigned int currentPosY,unsigned int previousPosX,unsigned int previousPosY);

    static std::vector<Pos> getIsTheirWay (std::vector<std::vector<CellState> > &field,Pos Start, Pos end,std::vector<bool (CellState::*)(void) const> arrayOfCallback);

    static std::vector<Pos> getNeighbors (const Pos &current, unsigned int fieldSize);



};

#endif // COLLISIONS_H
