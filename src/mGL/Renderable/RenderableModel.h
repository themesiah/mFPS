#ifndef MGL_RENDERABLEMODEL
#define MGL_RENDERABLEMODEL

#include "RenderableObject.h"

namespace mGL
{
	class RenderableModel : public RenderableObject
	{
	public:
		RenderableModel();
		RenderableModel(tinyxml2::XMLElement* element);
		RenderableModel(std::vector<Mesh*> meshes);
		RenderableModel(tinyxml2::XMLElement* element, std::vector<Mesh*> meshes);
		RenderableModel(RenderableModel& ro);
		RenderableModel& operator=(RenderableModel& ro);
		~RenderableModel();
		void Render(const glm::mat4& projection, const glm::mat4& view) override;
		std::vector<Mesh*> GetMeshes() const;
	private:
		std::vector<Mesh*> mMeshes;
	};
}

#endif