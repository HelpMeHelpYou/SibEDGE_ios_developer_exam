#ifndef CELLSTATE_H
#define CELLSTATE_H


class CellState
{
public:
    CellState(){}

    void SetIsGamer (bool gamer) {_isGamer = gamer;}
    void SetIsGold (bool gold) {_isGold = gold;}
    void SetIsRobot (bool robot) {_isRobot = robot;}
    void SetIsHoles (bool holes) {_isHoles = holes;}

    bool GetIsGamer (void) const {return _isGamer;}
    bool GetIsGold (void) const {return _isGold;}
    bool GetIsRobot (void) const {return _isRobot;}
    bool GetIsHoles (void) const {return _isHoles;}
    bool GetIsBusy (void) const {return _isGamer || _isGold || _isRobot ||_isHoles;}

private:
    bool _isGamer = false;
    bool _isGold = false;
    bool _isRobot = false;
    bool _isHoles = false;
};

#endif // CELLSTATE_H
