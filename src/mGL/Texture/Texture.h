#ifndef MGL_TEXTURE
#define MGL_TEXTURE

#include <GL/glew.h> // include GLEW and new version of GL on Windowsç
#include <string>
#define STB_IMAGE_IMPLEMENTATION


namespace mGL {
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& path);
		~Texture();
		void Load(const std::string& path);
		void Use() const;
	private:
		unsigned char* mData;
		int mWidth;
		int mHeight;
		int mChannels;
		unsigned int mTextureId;
	};
}

#endif
