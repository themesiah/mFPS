#include "Renderer.h"
#include <vector>

namespace mGL {
    int Renderer::Init()
    {
        // start GL context and O/S window using the GLFW helper library
        if (!glfwInit()) {
            fprintf(stderr, "ERROR: could not start GLFW3\n");
            return 1;
        }

        _window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
        if (!_window) {
            fprintf(stderr, "ERROR: could not open window with GLFW3\n");
            glfwTerminate();
            return 1;
        }
        glfwMakeContextCurrent(_window);

        // start GLEW extension handler
        glewExperimental = GL_TRUE;
        glewInit();

        // get version info
        const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString(GL_VERSION); // version as a string
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version supported %s\n", version);

        // tell GL to only draw onto a pixel if the shape is closer to the viewer
        glEnable(GL_DEPTH_TEST); // enable depth-testing
        glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

        

        // Create triangle points
        std::vector<float> points = {
            0.0f,  0.5f,  0.0f, // Top
            0.5f, -0.5f,  0.0f, // Down right
            -0.5f, -0.5f,  0.0f // Down left
        }; // 0 is center, -1 is left / bottom, 1 is right / top

        std::vector<float> points2 = {
            -0.5f, 0.5f, 0.0f, // Top left
            0.5f, 0.5f, 0.0f, // Top right
            0.0f, -0.5f, 0.0f // Bottom
        };

        _meshes.push_back(Mesh(points));
        _meshes.push_back(Mesh(points2));

        std::vector<float> points3 = {
            // FRONT
            -0.5f, 0.5f, -0.5f, // top left
            0.5f, 0.5f, -0.5f, // top right
            0.5f, -0.5f, -0.5f, // bot right
            -0.5f, 0.5f, -0.5f, // top left
            0.5f, -0.5f, -0.5f, // bot right
            -0.5f, -0.5f, -0.5f, // bot left
        
            // TOP
            -0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
        
            // RIGHT
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f
        
            // LEFT
            - 0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
        
            // BOTTOM
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,
        
            // BACK
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
        };
        //_meshes.push_back(Mesh(points3));

        _vao = 0;
        unsigned int vbo = 0;
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        _shader.Init("Data/Shader/vertexTest.gls", "Data/Shader/pixelTest.gls");
        return 0;
    }

    void Renderer::DoTriangle()
    {
        while (!glfwWindowShouldClose(_window)) {
            
            // wipe the drawing surface clear
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            _shader.Use();
            glBindVertexArray(_vao);

            for (int i = 0; i < _meshes.size(); ++i)
            {
                _meshes[i].Render();
            }
            
            // update other events like input handling 
            glfwPollEvents();
            // put the stuff we've been drawing onto the display
            glfwSwapBuffers(_window);
        }
    }

    void Renderer::Terminate()
    {
        // close GL context and any other GLFW resources
        glfwTerminate();
    }
}