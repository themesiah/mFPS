#ifndef MGL_MATERIAL
#define MGL_MATERIAL

#include <memory>
#include <vector>
#include "Shader.h"

namespace mGL
{
	class IMaterialParameter;

	class Material
	{
	public:
		Material();
		Material(Shader* shader);
		~Material();
		void Use();
		void AddParameter(IMaterialParameter* parameter);
		Shader* GetShader();
	private:
		std::shared_ptr<Shader> mShader;
		std::vector<IMaterialParameter*> mParameters;
	};
}

#endif