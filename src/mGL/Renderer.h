#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "RenderableObject.h"
#include "Texture.h"

namespace mGL {
	class Renderer
	{
	public:
		int InitializeRenderer();
		void Render();
		void Terminate();
	private:
		GLFWwindow* _window;
		RenderableObject mRenderableObject;
	};
}
#endif