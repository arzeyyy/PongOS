#include "Game.h"


struct gfxRect ball = {
    5, 5,
    SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
    255,
    5, 5};

struct gfxRect paddle1 = {
    5, 36,
    10, 82,
    COLOR_WHITE,
    7, 7};

struct gfxRect paddle2 = {
    5, 36,
    305, 82,
    COLOR_WHITE,
    7, 7};

uint_16 score_right;
uint_16 score_left;

bool ball_draw = true;
uint_64 ball_freeze;

// static bool single_player;

bool check_collision(struct gfxRect *a, struct gfxRect *b)
{
    if (a->pos_x<b->pos_x + b->width &
                 a->pos_x + a->width>
            b->pos_x &
        a->pos_y<b->pos_y + b->height &
                 a->height + a->pos_y>
            b->pos_y)
        return true;
}

void game_ball()
{
    if (check_collision(&ball, &paddle1))
    {
        ball.speed_x *= -1;
    }
    if (check_collision(&ball, &paddle2))
    {
        ball.speed_x *= -1;
    }

    if (ball.pos_x >= SCREEN_WIDTH)
    {
        ball_freeze = timer_get() + 20;
        if(ball_draw)
            score_left++;

        ball_draw = false;

        ball.speed_x *= -1;
    }
    if (ball.pos_x <= 1)
    {
        ball_freeze = timer_get() + 20;
        if (ball_draw)
            score_right++;

        ball_draw = false;

        ball.speed_x *= -1;
    }

    if (ball.pos_y >= SCREEN_HEIGHT)
    {
        ball.pos_y = SCREEN_HEIGHT;
        ball.speed_y *= -1;
    }
    if (ball.pos_y <= 0)
    {
        ball.pos_y = 0;
        ball.speed_y *= -1;
    }

    if (!ball_draw && ball_freeze < timer_get())
    {
        ball.pos_x = SCREEN_WIDTH / 2;
        ball.pos_y = SCREEN_HEIGHT / 2;

        ball_draw = true;
    }

    rect_move(&ball, ball.speed_x, ball.speed_y);
}

void game_paddle1()
{
    if (is_key_pressed(KEY_W) && paddle1.pos_y > 5)
    {
        rect_move(&paddle1, 0, -paddle1.speed_y);
    }
    if (is_key_pressed(KEY_S) && paddle1.pos_y < SCREEN_HEIGHT - paddle1.height - 5)
    {
        rect_move(&paddle1, 0, paddle1.speed_y);
    }
}

void game_paddle2_m()
{
    if (is_key_pressed(KEY_UP) && paddle2.pos_y > 5)
    {
        rect_move(&paddle2, 0, -paddle2.speed_y);
    }
    if (is_key_pressed(KEY_DOWN) && paddle2.pos_y < SCREEN_HEIGHT - paddle2.height - 5)
    {
        rect_move(&paddle2, 0, paddle2.speed_y);
    }
}
void game_paddle2_s()
{
    if (ball.pos_y > 5 && ball.pos_y + paddle2.height < SCREEN_HEIGHT - 5)
        rect_set_pos(&paddle2, paddle2.pos_x, ball.pos_y);

}
    


void game_update()
{
    game_paddle1();

    if (single_player)
        game_paddle2_s();
    else
        game_paddle2_m();


    game_ball();
}



void game_draw()
{
    if(ball_draw)
        rect_draw(&ball);
        
    rect_draw(&paddle1);
    rect_draw(&paddle2);
    font_draw(to_string(score_left), 135, 15);
    font_draw(to_string(score_right), 165, 15);

}


