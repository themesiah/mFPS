#include <memory>

#include "Game.h"

int main()
{
    std::unique_ptr<mFPS::Game> game = std::make_unique<mFPS::Game>();
    game->Initialize(1280, 720);

    while (game->Update())
    {
    }

    return 0;
}