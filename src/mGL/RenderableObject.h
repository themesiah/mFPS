#ifndef MGL_RENDERABLE_OBJECT
#define MGL_RENDERABLE_OBJECT

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


namespace mGL
{
	class Mesh;
	class Material;
	class RenderableObject
	{
	public:
		RenderableObject();
		RenderableObject(std::vector<Mesh> meshes);
		std::shared_ptr<glm::mat4> GetMatrix();
		void Render();
		void SetMaterial(Material* material);
	private:
		std::vector<Mesh> mMeshes;
		std::shared_ptr<glm::mat4> mMatrix;
		std::shared_ptr<Material> mMaterial;
	};
};

#endif