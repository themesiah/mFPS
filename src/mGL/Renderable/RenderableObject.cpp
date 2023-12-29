#include "RenderableObject.h"
#include "../Mesh.h"
#include "../Material/Material.h"
#include <glm/gtc/type_ptr.hpp>

namespace mGL
{
	RenderableObject::RenderableObject() : mMatrix(new glm::mat4(1.0f))
	{
	}

	RenderableObject::RenderableObject(RenderableObject& ro)
	{
		mMatrix = ro.mMatrix;
	}

	RenderableObject& RenderableObject::operator=(RenderableObject& ro)
	{
		mMatrix = ro.mMatrix;

		return *this;
	}

	RenderableObject::~RenderableObject()
	{
	}

	std::shared_ptr<glm::mat4> RenderableObject::GetMatrix() const
	{
		return mMatrix;
	}
}