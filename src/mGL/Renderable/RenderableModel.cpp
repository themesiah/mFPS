#include "RenderableModel.h"

namespace mGL
{
	RenderableModel::RenderableModel() : RenderableObject(), mMeshes(std::vector<Mesh *>())
	{
	}

	RenderableModel::RenderableModel(tinyxml2::XMLElement *element) : RenderableObject(element), mMeshes(std::vector<Mesh *>())
	{
	}

	RenderableModel::RenderableModel(tinyxml2::XMLElement *element, std::vector<Mesh *> meshes) : RenderableObject(element), mMeshes(meshes)
	{
	}

	RenderableModel::RenderableModel(std::vector<Mesh *> meshes) : RenderableObject(), mMeshes(meshes)
	{
	}

	RenderableModel::RenderableModel(RenderableModel &ro) : RenderableObject()
	{
		mMeshes = ro.mMeshes;
		mMatrix = ro.mMatrix;
		mName = ro.mName;
	}

	RenderableModel &RenderableModel::operator=(RenderableModel &ro)
	{
		mMeshes = ro.mMeshes;
		mMatrix = ro.mMatrix;
		mName = ro.mName;

		return *this;
	}

	RenderableModel::~RenderableModel()
	{
		for (size_t i = 0; i < mMeshes.size(); ++i)
		{
			delete mMeshes[i];
		}
	}

	void RenderableModel::Render(const glm::mat4 &projection, const glm::mat4 &view)
	{
		for (size_t i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes[i]->Render(mMatrix.get(), projection, view);
		}
	}

	std::vector<Mesh *> RenderableModel::GetMeshes() const
	{
		return mMeshes;
	}
}