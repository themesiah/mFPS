#ifndef MGL_RENDERABLE_OBJECT
#define MGL_RENDERABLE_OBJECT

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "../Mesh.h"

namespace tinyxml2
{
	class XMLElement;
}

namespace mGL
{
	class RenderableObject
	{
	public:
		RenderableObject();
		RenderableObject(tinyxml2::XMLElement* element);
		RenderableObject(RenderableObject& ro);
		RenderableObject& operator=(RenderableObject& ro);
		virtual ~RenderableObject();
		void SetName(const std::string& name);
		std::shared_ptr<glm::mat4> GetMatrix() const;
		virtual void Render(const glm::mat4& projection, const glm::mat4& view) = 0;
#ifdef _DEBUG
		void ShowImGui();
#endif
	protected:
		std::string mName;
		std::shared_ptr<glm::mat4> mMatrix;
	};
};

#endif