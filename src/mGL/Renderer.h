#ifndef MGL_RENDERER
#define MGL_RENDERER

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <vector>

#include "Renderable/RenderableObject.h"

namespace mGL {
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		GLFWwindow* InitializeRenderer(const int& width, const int& height);
		void Render(std::vector<RenderableObject*> renderableObjects, const glm::mat4& projection, const glm::mat4& view);
		void EndFrame();
		void Terminate();
	private:
		GLFWwindow* mWindow;
	};
}
#endif