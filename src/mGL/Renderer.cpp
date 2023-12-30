#include "Renderer.h"

#include "mBase/Logger.h"
#include <sstream>

namespace mGL {
    Renderer::Renderer() : mWindow() {}

    Renderer::~Renderer(){}

    GLFWwindow* Renderer::InitializeRenderer(const int& width, const int& height)
    {
        // start GL context and O/S window using the GLFW helper library
        if (!glfwInit()) {
            fprintf(stderr, "ERROR: could not start GLFW3\n");
            return nullptr;
        }

        mWindow = glfwCreateWindow(width, height, "mFPS", NULL, NULL);
        if (!mWindow) {
            fprintf(stderr, "ERROR: could not open window with GLFW3\n");
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(mWindow);

        // start GLEW extension handler
        glewExperimental = GL_TRUE;
        glewInit();

        // get version info
        const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString(GL_VERSION); // version as a string
        
        std::stringstream ss;
        std::stringstream ss2;
        ss << "Renderer:\n" << renderer;
        ss2 << "OpenGL version supported:\n" << version;
        Logger::Log("Renderer", ss.str());
        Logger::Log("Renderer", ss2.str());

        // tell GL to only draw onto a pixel if the shape is closer to the viewer
        glEnable(GL_DEPTH_TEST); // enable depth-testing
        glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

        // Configure textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        return mWindow;
    }

    void Renderer::Render(std::vector<RenderableObject*> renderableObjects, const glm::mat4 &projection, const glm::mat4 &view)
    {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render all objects that need to be rendered
        for (int i = 0; i < renderableObjects.size(); ++i)
        {
            renderableObjects[i]->Render(projection, view);
        }
    }

    void Renderer::EndFrame()
    {
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(mWindow);
    }

    void Renderer::Terminate()
    {
        // close GL context and any other GLFW resources
        glfwTerminate();
    }
}