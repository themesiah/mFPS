#ifndef MGL_MATERIAL
#define MGL_MATERIAL

#include <memory>
#include <vector>
#include "../Shader.h"

namespace mGL
{
	class IMaterialParameter;

	class Material
	{
	public:
		Material();
		Material(Shader* shader);
		Material(const Material& m);
		Material& operator=(const Material& m);
		~Material();
		void Use() const;
		void AddParameter(IMaterialParameter* parameter);
		Shader* GetShader() const;
	private:
		std::shared_ptr<Shader> mShader;
		std::vector<IMaterialParameter*> mParameters;
	};
}

#endif