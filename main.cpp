#include "Game.h"


int main() {
    mFPS::Game game;
    game.Initialize(640, 480);

    while (game.Update())
    {
    }

    return 0;
}