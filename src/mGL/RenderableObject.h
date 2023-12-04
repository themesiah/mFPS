#ifndef MGL_RENDERABLE_OBJECT
#define MGL_RENDERABLE_OBJECT

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Mesh.h"


namespace mGL
{
	class RenderableObject
	{
	public:
		RenderableObject();
		RenderableObject(std::vector<Mesh> meshes);
		std::shared_ptr<glm::mat4> GetMatrix() const;
		void Render();
	private:
		std::vector<Mesh> mMeshes;
		std::shared_ptr<glm::mat4> mMatrix;
	};
};

#endif