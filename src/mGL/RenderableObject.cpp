#include "RenderableObject.h"
#include "Mesh.h"
#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

namespace mGL
{
	RenderableObject::RenderableObject() : mMeshes(std::vector<Mesh>()), mMatrix(new glm::mat4(1.0f)), mMaterial(nullptr)
	{
	}

	RenderableObject::RenderableObject(std::vector<Mesh> meshes) : mMeshes(meshes), mMatrix(new glm::mat4(1.0f)), mMaterial(nullptr)
	{
	}

	void RenderableObject::SetMaterial(Material* material)
	{
		mMaterial = std::shared_ptr<Material>(material);
	}

	std::shared_ptr<glm::mat4> RenderableObject::GetMatrix() const
	{
		return mMatrix;
	}

	void RenderableObject::Render()
	{
		mMaterial.get()->Use();
		mMaterial.get()->GetShader()->SetUniform1i("albedo", 0);
		mMaterial.get()->GetShader()->SetUniformMatrix4fv("transform", *mMatrix.get());
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes[i].Render();
		}
	}
}