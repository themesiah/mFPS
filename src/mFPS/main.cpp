#include "Game.h"

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    mFPS::Game* game = new mFPS::Game();
    game->Initialize(640, 480);

    while (game->Update())
    {
    }

    delete game;

    return 0;
}