#ifndef MGL_MATERIALPARAMETER
#define MGL_MATERIALPARAMETER

#include <glm/glm.hpp>

namespace mGL
{
	class Shader;
	class IMaterialParameter
	{
	public:
		virtual void Bind(Shader* shader) const = 0;
	};

	class MaterialColorParameter : public IMaterialParameter
	{
	public:
		MaterialColorParameter();
		MaterialColorParameter(glm::vec4 color);
		MaterialColorParameter(float r, float g, float b, float a);
		void Bind(Shader* shader) const;
	private:
		glm::vec4 mColor;
	};
}

#endif
