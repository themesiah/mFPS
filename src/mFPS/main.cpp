#include "Game.h"


int main() {
    mFPS::Game* game = new mFPS::Game();
    game->Initialize(640, 480);

    while (game->Update())
    {
    }

    delete game;

    return 0;
}