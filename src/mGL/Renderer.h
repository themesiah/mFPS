#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include "Mesh.h"

namespace mGL {
	class Renderer
	{
	public:
		int Init();
		void DoTriangle();
		void Terminate();
	private:
		GLFWwindow* _window;
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _shaderProgram;
		std::vector<Mesh> _meshes;
	};
}
#endif