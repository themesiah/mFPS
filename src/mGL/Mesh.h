#ifndef MGL_MESH
#define MGL_MESH

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <vector>

namespace mGL
{
	class Mesh
	{
	public:
		Mesh(std::vector<float> vertices);
		void SetVertices(std::vector<float> vertices);
		void Render();
	private:
		std::vector<float> _vertices;
	};
}

#endif