#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

class Renderer
{
public:
	int Init();
	void DoTriangle();
	void Terminate();
private:
	GLFWwindow* window;
	GLuint vao;
};

#endif