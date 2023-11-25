#include "mGL/Renderer.h"

int main() {
    mGL::Renderer r;
    int result = r.Init();
    if (result != 0) {
        return result;
    }

    r.DoTriangle();

    r.Terminate();
    return 0;
}