#include "Game.h"

Game::Game(/* args */)
{
}

void Game::Init()
{
    last_tick = timer_get();
}

void Game::Run()
{
    uint_64 curr_tick = timer_get();
    float delta_time = (curr_tick / last_tick) / (float) state.freq;
    last_tick = curr_tick;
}
