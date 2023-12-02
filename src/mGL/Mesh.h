#ifndef MGL_MESH
#define MGL_MESH

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <vector>

namespace mGL
{
	struct Vertex;
	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
		void Render() const;
		void SetupMesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
	private:
		unsigned int mVAO;
		unsigned int mVBO;
		unsigned int mEBO;
		unsigned int mIndicesSize;
	};
}

#endif