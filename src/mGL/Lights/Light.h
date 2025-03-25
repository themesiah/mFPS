#ifndef MGL_LIGHT
#define MGL_LIGHT

#include <memory>
#include <glm/glm.hpp>
#include <string>

namespace tinyxml2
{
	class XMLElement;
}

namespace mGL
{
	class RenderableObject;
	class RenderableModel;
	class Light
	{
	public:
		Light(tinyxml2::XMLElement *element);
		virtual ~Light();
		virtual void Set() = 0;
		std::shared_ptr<glm::mat4> GetMatrix() const;
		std::string GetName() const;
		void SetColor(const glm::vec3 &color);
		void SetIntensity(const float &intensity);
#ifdef EDITOR_MODE
		bool StartImGui();
		std::shared_ptr<RenderableObject> GetIcon() const;
#endif
	protected:
#ifdef EDITOR_MODE
		virtual bool ShowImGui() = 0;
#endif
		std::string mName;
		std::shared_ptr<glm::mat4> mMatrix;
		float mIntensity;
		glm::vec3 mColor;
		unsigned int mSSBO;

	private:
		std::shared_ptr<RenderableModel> mIcon;
	};
}

#endif