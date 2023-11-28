#include "Shader.h"

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <fstream>
#include <iostream>
#include <streambuf>
#include <glm/gtc/type_ptr.hpp>

namespace mGL
{
	const char* DEFAULT_VERTEX_SHADER =
		"#version 400\n"
		"layout (location = 0) in vec3 vp;" // Location 0 references the first parameter of glVertexAttribPointer
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";

	const char* DEFAULT_PIXEL_SHADER =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(1.0, 0.0, 1.0, 1.0);"
		"}";

	Shader::Shader() : mVertexShaderFilePath(""), mPixelShaderFilePath(""), mShaderProgram(0)
	{

	}

	Shader::Shader(std::string vertexShaderFilePath, std::string pixelShaderFilePath)
	{
		Init(vertexShaderFilePath, pixelShaderFilePath);
	}

	void Shader::Init(std::string vertexShaderFilePath, std::string pixelShaderFilePath)
	{
		mVertexShaderFilePath = vertexShaderFilePath;
		mPixelShaderFilePath = pixelShaderFilePath;

		std::ifstream vertexFile("Data/Shader/"+ mVertexShaderFilePath);
		std::ifstream pixelFile("Data/Shader/"+ mPixelShaderFilePath);

		std::string vertexShader;
		std::string pixelShader;

		if (vertexFile.is_open())
		{
			vertexShader = std::string((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
		}
		else
		{
			std::cout << "Vertex shader file with name " << mVertexShaderFilePath << " not found. Loading default";
			vertexShader = DEFAULT_VERTEX_SHADER;
		}

		if (pixelFile.is_open())
		{
			pixelShader = std::string((std::istreambuf_iterator<char>(pixelFile)), std::istreambuf_iterator<char>());
		}
		else {
			std::cout << "Pixel shader file with name " << mPixelShaderFilePath << " not found. Loading default";
			pixelShader = DEFAULT_PIXEL_SHADER;
		}

		const char* c_vertexShader = vertexShader.c_str();
		const char* c_pixelShader = pixelShader.c_str();

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &c_vertexShader, NULL);
		glCompileShader(vs);
		CheckCompileErrors(vs, "VERTEX");
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &c_pixelShader, NULL);
		glCompileShader(fs);
		CheckCompileErrors(fs, "PIXEL");

		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, fs);
		glAttachShader(mShaderProgram, vs);
		glLinkProgram(mShaderProgram);
		CheckCompileErrors(mShaderProgram, "PROGRAM");

		glDeleteShader(fs);
		glDeleteShader(vs);

		vertexFile.close();
		pixelFile.close();
	}

	void Shader::UseShader()
	{
		glUseProgram(mShaderProgram);
	}

	void Shader::Reload()
	{
		Init(mVertexShaderFilePath, mPixelShaderFilePath);
	}

	unsigned int Shader::GetProgram()
	{
		return mShaderProgram;
	}

	void Shader::SetUniform4f(const std::string &locationString, glm::vec4 value) const
	{
		int location = glGetUniformLocation(mShaderProgram, locationString.c_str());
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}

	void Shader::SetUniformMatrix4fv(const std::string &locationString, glm::mat4 value) const
	{
		int location = glGetUniformLocation(mShaderProgram, locationString.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::CheckCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}