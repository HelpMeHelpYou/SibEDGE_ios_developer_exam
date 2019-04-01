#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>

#include "cellstate.h"

struct Pos
{
    unsigned int X;
    unsigned int Y;
};

class collisions
{
    bool isInitCollisions(std::vector<std::vector<CellState> > & field,
                          CellState& future,
                          Pos currentPos);

    bool gameCollisions(CellState& previous,CellState& future,unsigned int currentPosX,unsigned int currentPosY,unsigned int previousPosX,unsigned int previousPosY);

    std::vector<Pos> getIsTheirWay (std::vector<std::vector<CellState> > &field,Pos Start, Pos end,std::vector<bool (CellState::*)(void)> arrayOfCallback);

    std::vector<Pos> getNeighbors (const Pos &current, unsigned int fieldSize);



};

#endif // COLLISIONS_H
