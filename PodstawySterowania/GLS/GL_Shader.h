/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_Shader
 * ----------------
 * Component responsible for managing OpenGL shader programs.
 * Loads, compiles, and links vertex and fragment shaders from source files.
 * Handles error reporting and logging with detailed status codes and timestamps.
 *
 * Internally stores shader source paths, compilation status, and shader program handle.
 * Provides methods for shader status retrieval and program management.
 *
 * Intended to serve as a reusable and extensible base for rendering systems
 * requiring dynamic shader management and diagnostics.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

#include "GL_Component.h"

namespace GLS{
	class GL_Shader:public GL_Component{
		std::string _vertexShaderPath; // Path to vertex shader source file
		std::string _fragmentShaderPath; // Path to fragment shader source file
		GLuint _shaderN; // Unique handle for the shader program
		GLint _shaderStatus; // B0000 good B1000 vertexShaderBad B0100 fragmentShaderBad B1100 both B0010 linkBad B0001 error reading file

		std::string _loadShader(const char*shaderPath); // Loads and returns shader source code as std::string
		GLuint _compileShader(const char*shaderPath,GLenum shaderType); // Compiles shader
		GLuint _createShaderProgram(const char*vertexShaderPath,const char*fragmentShaderPath); // Links two shaders together into shader program
		std::string _getCurrentSystemTime()const; // Method for getting current system time yyyy_mm_dd_hh_mm_ss
		std::string _getLogFilePath()const;
	public:
		GL_Shader(const char*vertexShaderPath,const char*fragmentShaderPath);
		GL_Shader(std::string vertexShaderPath,std::string fragmentShaderPath);
		~GL_Shader();
		GLuint getShaderID()const; // Returns shader's GPU handle
		GLuint getShaderStatus()const; // Returns shader's linking status
	};
}
