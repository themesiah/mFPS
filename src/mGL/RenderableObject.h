#ifndef MGL_RENDERABLE_OBJECT
#define MGL_RENDERABLE_OBJECT

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "Shader.h"
#include <memory>

namespace mGL
{
	class RenderableObject
	{
	public:
		RenderableObject();
		RenderableObject(std::vector<Mesh> meshes);
		std::shared_ptr<glm::mat4> GetMatrix();
		void Render();
		void SetShader(Shader shader);
	private:
		std::vector<Mesh> mMeshes;
		std::shared_ptr<glm::mat4> mMatrix;
		Shader mShader;
	};
};

#endif