#include "Shader.h"

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <fstream>
#include <iostream>
#include <streambuf>

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

	Shader::Shader()
	{

	}

	Shader::Shader(std::string vertexShaderFilePath, std::string pixelShaderFilePath)
	{
		Init(vertexShaderFilePath, pixelShaderFilePath);
	}

	void Shader::Init(std::string vertexShaderFilePath, std::string pixelShaderFilePath)
	{
		_vertexShaderFilePath = vertexShaderFilePath;
		_pixelShaderFilePath = pixelShaderFilePath;

		std::ifstream vertexFile(_vertexShaderFilePath);
		std::ifstream pixelFile(_pixelShaderFilePath);

		std::string vertexShader;
		std::string pixelShader;

		if (vertexFile.is_open())
		{
			vertexShader = std::string((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
		}
		else
		{
			std::cout << "Vertex shader file with path " << _vertexShaderFilePath << " not found. Loading default";
			vertexShader = DEFAULT_VERTEX_SHADER;
		}

		if (pixelFile.is_open())
		{
			pixelShader = std::string((std::istreambuf_iterator<char>(pixelFile)), std::istreambuf_iterator<char>());
		}
		else {
			std::cout << "Pixel shader file with path " << _pixelShaderFilePath << " not found. Loading default";
			pixelShader = DEFAULT_PIXEL_SHADER;
		}

		const char* c_vertexShader = vertexShader.c_str();
		const char* c_pixelShader = pixelShader.c_str();

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &c_vertexShader, NULL);
		glCompileShader(vs);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &c_pixelShader, NULL);
		glCompileShader(fs);

		_shaderProgram = glCreateProgram();
		glAttachShader(_shaderProgram, fs);
		glAttachShader(_shaderProgram, vs);
		glLinkProgram(_shaderProgram);

		vertexFile.close();
		pixelFile.close();
	}

	void Shader::Use()
	{
		glUseProgram(_shaderProgram);
	}
}