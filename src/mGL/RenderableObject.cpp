#include "RenderableObject.h"

#include <glm/gtc/type_ptr.hpp>

namespace mGL
{
	RenderableObject::RenderableObject() : mMeshes(std::vector<Mesh>()), mMatrix(new glm::mat4(1.0f))
	{
	}

	RenderableObject::RenderableObject(std::vector<Mesh> meshes) : mMeshes(meshes), mMatrix(new glm::mat4(1.0f))
	{
	}

	void RenderableObject::SetShader(Shader shader)
	{
		mShader = shader;
	}

	std::shared_ptr<glm::mat4> RenderableObject::GetMatrix()
	{
		return mMatrix;
	}

	void RenderableObject::Render()
	{
		unsigned int transformLoc = glGetUniformLocation(mShader.GetProgram(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*mMatrix));
		mShader.UseShader();
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes[i].Render();
		}
	}
}