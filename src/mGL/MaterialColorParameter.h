#ifndef MGL_MATERIAL_COLOR_PARAMETER
#define MGL_MATERIAL_COLOR_PARAMETER

#include "IMaterialParameter.h"

namespace mGL {
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