#include "mGL/Renderer.h"
#include "mGL/MeshFactory.h"

int main() {
    mGL::Renderer r;
    int result = r.InitializeRenderer();
    if (result != 0) {
        return result;
    }
    
    r.Render();
    
    r.Terminate();
    return 0;
}