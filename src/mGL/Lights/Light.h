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
	class Light
	{
	public:
		Light(tinyxml2::XMLElement* element);
		virtual ~Light();
		virtual void Set() = 0;
		std::shared_ptr<glm::mat4> GetMatrix() const;
		void SetColor(const glm::vec3 &color);
		void SetIntensity(const float& intensity);
#ifdef _DEBUG
		void StartImGui();
#endif
	protected:
#ifdef _DEBUG
		virtual void ShowImGui() = 0;
#endif
		std::string mName;
		std::shared_ptr<glm::mat4> mMatrix;
		float mIntensity;
		glm::vec3 mColor;
		unsigned int mSSBO;
	};
}

#endif