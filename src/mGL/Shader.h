#ifndef MGL_SHADER
#define MGL_SHADER

#include <string>

namespace mGL
{
	class Shader
	{
	public:
		Shader();
		Shader(std::string vertexShaderFilePath, std::string pixelShaderFilePath);
		void UseShader();
		void Init(std::string vertexShaderFilePath, std::string pixelShaderFilePath);
		void Reload();
	private:
		std::string mVertexShaderFilePath;
		std::string mPixelShaderFilePath;
		unsigned int mShaderProgram;
	};	
}

#endif