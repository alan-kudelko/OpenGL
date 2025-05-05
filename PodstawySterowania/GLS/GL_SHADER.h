#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

namespace GLS{
	class GL_SHADER{
		std::string _vertexShaderPath;
		std::string _fragmentShaderPath;
		GLuint _shaderN;
		GLint _shaderStatus; // B0000 good B1000 vertexShaderBad B0100 fragmentShaderBad B1100 both B0010 linkBad B0001 error reading file

		std::string _loadShader(const char*shaderPath);
		GLuint _compileShader(const char*shaderPath,GLenum shaderType);
		GLuint _createShaderProgram(const char*vertexShaderPath,const char*fragmentShaderPath);
		std::string _getCurrentSystemTime()const;
		std::string _getLogFilePath()const;
	public:
		GL_SHADER(const char*vertexShaderPath,const char*fragmentShaderPath);
		GL_SHADER(std::string vertexShaderPath,std::string fragmentShaderPath);
		~GL_SHADER();
		GLuint getShaderID()const;
		GLuint getShaderStatus()const;
	};
}
/*
	Klasa słuzaca do kompilacji oraz linkowania shaderow
	Zadaniami klasy jest:
	3. Zapisywanie logow kompilacji do pliku z sygnatura czasowa
	4. Przechowywanie opisu shaderow?
	5. Używanie i nieużywanie danego shadera
	I append do pliku
*/
