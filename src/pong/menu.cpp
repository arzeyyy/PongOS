#include "menu.h"

bool mode_choose_scene;
bool game_scene;
bool start_scene = true;

bool single_player;

void menu_update()
{
    if (!game_scene && is_key_pressed(key_any()))
    {
        mode_choose_scene = true;
        start_scene = false;
    }

    if(!game_scene && !start_scene && is_key_pressed(KEY_1))
    {
        mode_choose_scene = false;
        game_scene = true;
        single_player = true;
    }

    if (!game_scene && !start_scene && is_key_pressed(KEY_2))
    {
        mode_choose_scene = false;
        game_scene = true;
        single_player = false;
    }


    if(game_scene)
        game_update();
}

void menu_draw()
{
    if(start_scene)
        font_draw("press any key to start", ((SCREEN_WIDTH / 2) - (23 * 8) / 2), (SCREEN_HEIGHT / 2) - (8 / 2));

    if (game_scene)
        game_draw();

    if (mode_choose_scene)
    {
        font_draw("SinglePlayer [1]", ((SCREEN_WIDTH / 2) - (17 * 8) / 2), 80 - (8 / 2));
        font_draw("MultiPlayer  [2]", ((SCREEN_WIDTH / 2) - (17 * 8) / 2), 120 - (8 / 2));
    }
}