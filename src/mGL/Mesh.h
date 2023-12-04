#ifndef MGL_MESH
#define MGL_MESH

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <vector>
#include <memory>
#include "glm/glm.hpp"

namespace mGL
{
	class Material;
	struct Vertex;
	class Mesh
	{
	public:
		Mesh();
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
		void Render(glm::mat4 *matrix) const;
		void SetupMesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
		void SetMaterial(Material* material);
	private:
		unsigned int mVAO;
		unsigned int mVBO;
		unsigned int mEBO;
		unsigned int mIndicesSize;
		std::shared_ptr<Material> mMaterial;
	};
}

#endif