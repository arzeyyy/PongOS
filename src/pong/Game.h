#ifndef GAME_H
#define GAME_H

#include "../drivers/timer.h"
#include "../kernel/util.h"
#include "../drivers/screen.h"

class Game
{
private:
    uint_64 last_tick;

public:
    Game(/* args */);
    void Init();
    void Run();

    float delta_time;
};


#endif