#ifndef MGL_SHADER
#define MGL_SHADER

#include <string>
#include <glm/glm.hpp>

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
		unsigned int GetProgram();
		void SetUniform4f(const std::string &locationString, glm::vec4 value) const;
		void SetUniformMatrix4fv(const std::string &locationString, glm::mat4 value) const;
	private:
		void CheckCompileErrors(unsigned int shader, std::string type);
		std::string mVertexShaderFilePath;
		std::string mPixelShaderFilePath;
		unsigned int mShaderProgram;
	};	
}

#endif