#include "RenderableModel.h"

namespace mGL
{
	RenderableModel::RenderableModel() : mMeshes(std::vector<Mesh*>()), RenderableObject()
	{
	}

	RenderableModel::RenderableModel(std::vector<Mesh*> meshes) : mMeshes(meshes), RenderableObject()
	{
	}

	RenderableModel::RenderableModel(RenderableModel& ro)
	{
		mMeshes = ro.mMeshes;
		mMatrix = ro.mMatrix;
	}

	RenderableModel& RenderableModel::operator=(RenderableModel& ro)
	{
		mMeshes = ro.mMeshes;
		mMatrix = ro.mMatrix;

		return *this;
	}

	RenderableModel::~RenderableModel()
	{
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			delete mMeshes[i];
		}
	}

	void RenderableModel::Render(const glm::mat4& projection, const glm::mat4& view)
	{
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes[i]->Render(mMatrix.get(), projection, view);
		}
	}
}