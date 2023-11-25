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
		void Use();
		void Init(std::string vertexShaderFilePath, std::string pixelShaderFilePath);
	private:
		std::string _vertexShaderFilePath;
		std::string _pixelShaderFilePath;
		unsigned int _shaderProgram;
	};	
}

#endif