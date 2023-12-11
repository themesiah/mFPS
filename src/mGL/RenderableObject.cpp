#include "RenderableObject.h"
#include "Mesh.h"
#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

namespace mGL
{
	RenderableObject::RenderableObject() : mMeshes(std::vector<Mesh*>()), mMatrix(new glm::mat4(1.0f))
	{
	}

	RenderableObject::RenderableObject(std::vector<Mesh*> meshes) : mMeshes(meshes), mMatrix(new glm::mat4(1.0f))
	{
	}

	RenderableObject::RenderableObject(RenderableObject& ro)
	{
		mMeshes = ro.mMeshes;
		mMatrix = ro.mMatrix;
	}

	RenderableObject& RenderableObject::operator=(RenderableObject& ro)
	{
		mMeshes = ro.mMeshes;
		mMatrix = ro.mMatrix;

		return *this;
	}

	RenderableObject::~RenderableObject()
	{
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			delete mMeshes[i];
		}
	}

	std::shared_ptr<glm::mat4> RenderableObject::GetMatrix() const
	{
		return mMatrix;
	}

	void RenderableObject::Render(const glm::mat4& projection, const glm::mat4& view)
	{
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes[i]->Render(mMatrix.get(), projection, view);
		}
	}
}