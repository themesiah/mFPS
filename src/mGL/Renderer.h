#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include <memory>
#include "RenderableObject.h"

namespace mGL {
	class CameraBase;
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		GLFWwindow* InitializeRenderer(const int& width, const int& height);
		void Render(CameraBase* camera);
		void Terminate();
	private:
		GLFWwindow* mWindow;
		std::shared_ptr<RenderableObject> mRenderableObject;
	};
}
#endif