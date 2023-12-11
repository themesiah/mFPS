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
		RenderableObject(RenderableObject& ro);
		RenderableObject& operator=(RenderableObject& ro);
		~RenderableObject();
		std::shared_ptr<glm::mat4> GetMatrix() const;
		void Render(const glm::mat4 &projection, const glm::mat4 &view);
	private:
		std::vector<Mesh> mMeshes;
		std::shared_ptr<glm::mat4> mMatrix;
	};
};

#endif