#ifndef MGL_MATERIAL_TEXTURE_PARAMETER
#define MGL_MATERIAL_TEXTURE_PARAMETER

#include "IMaterialParameter.h"

namespace mGL {
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
		MaterialTextureParameter(TextureType texType, Texture* tex);
		~MaterialTextureParameter();
		void Bind(Shader* shader) const;
	private:
		Texture* mTexture;
		TextureType mTextureType;
	};
}

#endif