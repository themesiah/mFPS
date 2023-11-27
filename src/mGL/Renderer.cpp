#include "Renderer.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

namespace mGL {
    int Renderer::InitializeRenderer()
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

        //_meshes.push_back(Mesh(points));
        //_meshes.push_back(Mesh(points2));

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

        std::vector<float> points4 = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
        std::vector<int> points4indices = { 0, 1, 3, 1, 2, 3 };
        std::vector<Mesh> meshes;
        meshes.push_back(Mesh(points4, points4indices));

        mVao = 0;
        unsigned int vbo = 0;
        unsigned int ebo = 0;
        glGenVertexArrays(1, &mVao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(mVao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        Shader shader;
        shader.Init("vertexTest.gls", "pixelTest.gls");

        mRenderableObject = RenderableObject(meshes);
        mRenderableObject.SetShader(shader);
        std::shared_ptr<glm::mat4> matrix = mRenderableObject.GetMatrix();
        *matrix = glm::rotate(*matrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
        return 0;
    }

    void Renderer::Render()
    {
        while (!glfwWindowShouldClose(_window)) {
            
            // wipe the drawing surface clear
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindVertexArray(mVao);

            mRenderableObject.Render();
            
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