#ifndef MGL_DIRLIGHT
#define MGL_DIRLIGHT

#include <memory>
#include <glm/glm.hpp>

namespace tinyxml2
{
	class XMLElement;
}

namespace mGL
{
	class DirectionalLight
	{
	public:
		DirectionalLight(tinyxml2::XMLElement* element);
		void Set();
		std::shared_ptr<glm::mat4> GetMatrix() const;
		//const float GetIntensity() const;
		//const glm::vec3 GetColor() const;
#ifdef _DEBUG
		void ShowImGui();
#endif
	private:
		std::shared_ptr<glm::mat4> mMatrix;
		glm::vec4 mDirection;
		glm::vec3 mColor;
		float mIntensity;
		unsigned int mSSBO;
	};
}

#endif