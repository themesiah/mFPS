#include "RenderableObject.h"
#include "Mesh.h"
#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

namespace mGL
{
	RenderableObject::RenderableObject() : mMeshes(std::vector<Mesh>()), mMatrix(new glm::mat4(1.0f))
	{
	}

	RenderableObject::RenderableObject(std::vector<Mesh> meshes) : mMeshes(meshes), mMatrix(new glm::mat4(1.0f))
	{
	}

	std::shared_ptr<glm::mat4> RenderableObject::GetMatrix() const
	{
		return mMatrix;
	}

	void RenderableObject::Render()
	{
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes[i].Render(mMatrix.get());
		}
	}
}