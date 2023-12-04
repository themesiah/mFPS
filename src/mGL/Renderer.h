#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include <memory>
#include "RenderableObject.h"

namespace mGL {
	class Renderer
	{
	public:
		int InitializeRenderer();
		void Render();
		void Terminate();
	private:
		GLFWwindow* _window;
		std::shared_ptr<RenderableObject> mRenderableObject;
	};
}
#endif