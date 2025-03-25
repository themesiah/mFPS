#ifndef MGL_MATERIAL_TEXTURE_PARAMETER
#define MGL_MATERIAL_TEXTURE_PARAMETER

#include <memory>

#include "IMaterialParameter.h"

namespace mGL
{
	class Texture;

	enum TextureType
	{
		Albedo = 0,
		Normal = 1
	};

	class MaterialTextureParameter : public IMaterialParameter
	{
	public:
		MaterialTextureParameter();
		MaterialTextureParameter(TextureType texType);
		MaterialTextureParameter(TextureType texType, std::shared_ptr<Texture> tex);
		MaterialTextureParameter(const MaterialTextureParameter &mtp);
		MaterialTextureParameter &operator=(const MaterialTextureParameter &mtp);
		virtual ~MaterialTextureParameter();
		void Bind(Shader *shader) const;

	private:
		std::shared_ptr<Texture> mTexture;
		TextureType mTextureType;
	};
}

#endif