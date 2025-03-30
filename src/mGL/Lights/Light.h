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
	enum BindBufferTarget
	{
		Directional = 3,
		Ambient = 4,
		Point = 5
	};
	class RenderableObject;
	class RenderableModel;
	class Light
	{
	public:
		Light(tinyxml2::XMLElement *element);
		virtual ~Light();
		virtual void Set(const size_t &offset) = 0;
		std::shared_ptr<glm::mat4> GetMatrix() const;
		std::string GetName() const;
		void SetColor(const glm::vec3 &color);
		void SetIntensity(const float &intensity);
		virtual BindBufferTarget GetBindBufferTarget() const = 0;
		virtual size_t GetBufferSize() const = 0;

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