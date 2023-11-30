#include "Renderer.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include "IMaterialParameter.h"

namespace mGL {
    int Renderer::InitializeRenderer()
    {
        // start GL context and O/S window using the GLFW helper library
        if (!glfwInit()) {
            fprintf(stderr, "ERROR: could not start GLFW3\n");
            return 1;
        }

        _window = glfwCreateWindow(640, 480, "KLK", NULL, NULL);
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
        

        // Create vertex array object (1), vertex buffer object (2) and element buffer object (3)
        mVao = 0;
        unsigned int vbo = 0;
        unsigned int ebo = 0;
        glGenVertexArrays(1, &mVao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(mVao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Vertex position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // UVs
        glEnableVertexAttribArray(1);

        // Configure textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // CREATE TEMP DATA TO TEST THINGS
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

        std::vector<Mesh> meshes;
        std::vector<float> cube = {
            // FRONT FACE
            -0.5f, 0.5f, -0.5f,         0.0f, 1.0f,     // TOP LEFT
            0.5f, 0.5f, -0.5f,         1.0f, 1.0f,      // TOP RIGHT
            0.5f, -0.5f, -0.5f,         1.0f, 0.0f,     // BOTTOM RIGHT
            -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,    // BOTTOM LEFT
            // RIGHT FACE
            0.5f, 0.5f, -0.5f,         0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,         1.0f, 1.0f,
            0.5f, -0.5f, 0.5f,         1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,         0.0f, 0.0f,
            // LEFT FACE
            -0.5f, 0.5f, 0.5f,         0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f,         1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,         1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
            // BOTTOM FACE
            -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,        1.0f, 1.0f,
            0.5f, -0.5f, 0.5f,        1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,        0.0f, 0.0f,
            // TOP FACE
            -0.5f, 0.5f, 0.5f,        0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,        1.0f, 1.0f,
            0.5f, 0.5f, -0.5f,        1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f,        0.0f, 0.0f,
            // BACK FACE
            0.5f, 0.5f, 0.5f,         0.0f, 1.0f,     // TOP LEFT
            -0.5f, 0.5f, 0.5f,         1.0f, 1.0f,      // TOP RIGHT
            -0.5f, -0.5f, 0.5f,         1.0f, 0.0f,     // BOTTOM RIGHT
            0.5f, -0.5f, 0.5f,         0.0f, 0.0f,    // BOTTOM LEFT
        };
        std::vector<int> cubeIndices = { 0,1,2,2,3,0,4,5,6,6,7,4,8,9,10,10,11,8,12,13,14,14,15,12,16,17,18,18,19,16,20,21,22,22,23,20 };
        meshes.push_back(Mesh(cube, cubeIndices));

            // positions                // uvs
        std::vector<float> points4 = {
            0.5f,  0.5f, 0.0f,          1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,          1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,         0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,         0.0f, 1.0f  // top left 
        };
        std::vector<int> points4indices = { 0, 1, 3, 1, 2, 3 };
        //meshes.push_back(Mesh(points4, points4indices));

        Shader* shader = new Shader();
        shader->Init("vertexTest.gls", "pixelTest.gls");

        mRenderableObject = RenderableObject(meshes);
        Material* material = new Material(shader);
        material->AddParameter(new MaterialColorParameter(1.0f, 1.0f, 1.0f, 1.0f));
        mRenderableObject.SetMaterial(material);
        std::shared_ptr<glm::mat4> matrix = mRenderableObject.GetMatrix();
        *matrix = glm::rotate(*matrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
        *matrix = glm::rotate(*matrix, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
        *matrix = glm::rotate(*matrix, glm::radians(15.0f), glm::vec3(1.0, 1.0, 0.0));

        tex = Texture("wall.jpg");
        return 0;
    }

    void Renderer::Render()
    {
        while (!glfwWindowShouldClose(_window)) {
            
            // wipe the drawing surface clear
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            std::shared_ptr<glm::mat4> matrix = mRenderableObject.GetMatrix();
            *matrix = glm::rotate(*matrix, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));

            glBindVertexArray(mVao);
            tex.Use();
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