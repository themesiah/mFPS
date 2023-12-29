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
		virtual ~IMaterialParameter() = 0;
	};
}

#endif
