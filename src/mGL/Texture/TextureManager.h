#ifndef MGL_TEXTUREMANAGER
#define MGL_TEXTUREMANAGER

#include <string>

#include "TemplatedMapVector.h"
#include "Texture.h"

namespace mGL
{
	class TextureManager : public mBase::TemplatedMapVector<Texture>
	{
	public:
		TextureManager();
		TextureManager(const TextureManager &);
		void operator=(const TextureManager &);
		~TextureManager();
		static TextureManager &GetInstance();
	};
}

#endif