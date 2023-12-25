#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Vertex.h"
#include "MeshFactory.h"
#include "CameraBase.h"
#include "Material.h"

namespace mGL {
    Renderer::Renderer(){}

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
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version supported %s\n", version);

        // tell GL to only draw onto a pixel if the shape is closer to the viewer
        glEnable(GL_DEPTH_TEST); // enable depth-testing
        glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

        // Configure textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        //std::vector<Mesh> meshes;
        //std::vector<Vertex> cube = {
        //    // FRONT FACE
        //    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),         glm::vec2(0.0f, 1.0f)},     // TOP LEFT
        //    Vertex{glm::vec3(0.5f, 0.5f, -0.5f),          glm::vec2(1.0f, 1.0f)},      // TOP RIGHT
        //    Vertex{glm::vec3(0.5f, -0.5f, -0.5f),         glm::vec2(1.0f, 0.0f)},     // BOTTOM RIGHT
        //    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),        glm::vec2(0.0f, 0.0f)},    // BOTTOM LEFT
        //    // RIGHT FACE                                              )
        //    Vertex{glm::vec3(0.5f, 0.5f, -0.5f),          glm::vec2(0.0f, 1.0f)},
        //    Vertex{glm::vec3(0.5f, 0.5f, 0.5f),           glm::vec2(1.0f, 1.0f)},
        //    Vertex{glm::vec3(0.5f, -0.5f, 0.5f),          glm::vec2(1.0f, 0.0f)},
        //    Vertex{glm::vec3(0.5f, -0.5f, -0.5f),         glm::vec2(0.0f, 0.0f)},
        //    // LEFT FACE                                               )
        //    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),          glm::vec2(0.0f, 1.0f)},
        //    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),         glm::vec2(1.0f, 1.0f)},
        //    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),        glm::vec2(1.0f, 0.0f)},
        //    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),         glm::vec2(0.0f, 0.0f)},
        //    // BOTTOM FACE                                             )
        //    Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),        glm::vec2(0.0f, 1.0f)},
        //    Vertex{glm::vec3(0.5f, -0.5f, -0.5f),         glm::vec2(1.0f, 1.0f)},
        //    Vertex{glm::vec3(0.5f, -0.5f, 0.5f),          glm::vec2(1.0f, 0.0f)},
        //    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),         glm::vec2(0.0f, 0.0f)},
        //    // TOP FACE                                                )
        //    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),          glm::vec2(0.0f, 1.0f)},
        //    Vertex{glm::vec3(0.5f, 0.5f, 0.5f),           glm::vec2(1.0f, 1.0f)},
        //    Vertex{glm::vec3(0.5f, 0.5f, -0.5f),          glm::vec2(1.0f, 0.0f)},
        //    Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),         glm::vec2(0.0f, 0.0f)},
        //    // BACK FACE
        //    Vertex{glm::vec3(0.5f, 0.5f, 0.5f),           glm::vec2(0.0f, 1.0f)},     // TOP LEFT
        //    Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),          glm::vec2(1.0f, 1.0f)},      // TOP RIGHT
        //    Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),         glm::vec2(1.0f, 0.0f)},     // BOTTOM RIGHT
        //    Vertex{glm::vec3(0.5f, -0.5f, 0.5f),          glm::vec2(0.0f, 0.0f)},    // BOTTOM LEFT
        //};
        //std::vector<unsigned short> cubeIndices = { 0,1,2,2,3,0,4,5,6,6,7,4,8,9,10,10,11,8,12,13,14,14,15,12,16,17,18,18,19,16,20,21,22,22,23,20 };
        //meshes.push_back(Mesh(cube, cubeIndices));

        //mRenderableObject = std::auto_ptr<RenderableObject>(MeshFactory::LoadObj("tree_thin_dark.obj"));
        //mRenderableObject = std::auto_ptr<RenderableObject>(MeshFactory::LoadObj("test_alex.obj"));
        mRenderableObject = std::auto_ptr<RenderableObject>(MeshFactory::LoadObj("vertex_color_test.obj"));

        //std::vector<Vertex> vertices = {
        //    { glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
        //    { glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
        //    { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
        //    { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f) }
        //};
        //std::vector<unsigned short> indices {0, 1, 2, 2, 3, 0};
        //Mesh* mesh = new Mesh(vertices, indices);
        //Shader* shader = new Shader("VertexUberShader.gls", "PixelUberShader.gls");
        //std::shared_ptr<Material> mat = std::shared_ptr<Material>(new Material(shader));
        //mesh->SetMaterial(mat);
        //std::vector<Mesh*> meshes = {
        //    mesh
        //};
        //mRenderableObject = std::auto_ptr<RenderableObject>(new RenderableObject(meshes));

        std::shared_ptr<glm::mat4> matrix = mRenderableObject->GetMatrix();
        //*matrix = glm::rotate(*matrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
        //*matrix = glm::rotate(*matrix, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
        //*matrix = glm::rotate(*matrix, glm::radians(15.0f), glm::vec3(1.0, 1.0, 0.0));
        //*matrix = glm::rotate(*matrix, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0));
        *matrix = glm::translate(*matrix, glm::vec3(0.0f, -1.6f, -8.5f));

        return mWindow;
    }

    void Renderer::Render(CameraBase* camera)
    {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 proj = camera->GetProjection();
        glm::mat4 view = camera->GetView();

        //std::shared_ptr<glm::mat4> matrix = mRenderableObject->GetMatrix();
        //*matrix = glm::rotate(*matrix, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
        mRenderableObject->Render(proj, view);

            
        // update other events like input handling 
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(mWindow);
    }

    void Renderer::Terminate()
    {
        // close GL context and any other GLFW resources
        glfwTerminate();
    }
}