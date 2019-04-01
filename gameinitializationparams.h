#ifndef GAMEINITIATIONPARAMS_H
#define GAMEINITIATIONPARAMS_H

struct GameinitializationParams
{
public:

    static constexpr unsigned int defualtChamberSize = 3;
    static constexpr unsigned int defualtRobotsNumber = 2;
    static constexpr unsigned int defualtGoldNumber = 1;
    static constexpr  unsigned int defualtHolesNumer = 1;
    unsigned int chamberSize = defualtChamberSize;
    unsigned int robotsNumber = defualtRobotsNumber;
    unsigned int goldNumber = defualtGoldNumber;
    unsigned int holesNumer = defualtHolesNumer;
};


#endif // GAMEINITIATIONPARAMS_H
