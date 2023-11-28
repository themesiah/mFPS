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
		Mesh(std::vector<float> vertices, std::vector<int> indices);
		void Render() const;
	private:
		void SetVertices(std::vector<float> vertices);
		void SetIndices(std::vector<int> indices);
		bool mUsingIndices;
		std::vector<float> mVertices;
		std::vector<int> mIndices;
	};
}

#endif