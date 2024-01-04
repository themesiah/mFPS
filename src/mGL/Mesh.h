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
		Mesh(const Mesh& m);
		Mesh& operator=(const Mesh& m);
		~Mesh();
		void Render(glm::mat4 *matrix, const glm::mat4& projection, const glm::mat4& view) const;
		void SetupMesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices);
		void SetMaterial(std::shared_ptr<Material> material);
		std::shared_ptr<Material> GetMaterial() const;
	private:
		unsigned int mVAO;
		unsigned int mVBO;
		unsigned int mEBO;
		unsigned int mIndicesSize;
		std::shared_ptr<Material> mMaterial;
	};
}

#endif