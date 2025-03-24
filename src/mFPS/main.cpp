#include "Game.h"

int main()
{
    mFPS::Game *game = new mFPS::Game();
    game->Initialize(1280, 720);

    while (game->Update())
    {
    }

    delete game;

    return 0;
}