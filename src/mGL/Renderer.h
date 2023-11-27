#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include "Mesh.h"
#include "Shader.h"

namespace mGL {
	class Renderer
	{
	public:
		int InitializeRenderer();
		void DoTriangle();
		void Terminate();
	private:
		GLFWwindow* _window;
		unsigned int mVao;
		std::vector<Mesh> mMeshes;
		Shader mShader;
	};
}
#endif