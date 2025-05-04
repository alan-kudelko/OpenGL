#pragma once

#include <sstream>
#include <fstream>
#include <ctime>

#include "GL_GPUResourceTracker.h"

extern GLS::GL_GPUResourceTracker GL_GPUresourceTracker;

namespace GLS{
	const char*GL_SHADER_LOG_FILENAME="GL_Shader";
	
	class GL_SHADER{
		std::string _vertexShaderPath;
		std::string _fragmentShaderPath;
		GLuint _shaderN;
	public:
		GL_SHADER();
		~GL_SHADER();
	};
}
/*
	Klasa słuzaca do kompilacji oraz linkowania shaderow
	Zadaniami klasy jest:
	1. Kompilacja oraz linkowanie shaderow
	2. Rejestrowanie oraz wyrejestrowywanie uzywanych shaderow
	3. Zapisywanie logow kompilacji do pliku z sygnatura czasowa
	4. Przechowywanie opisu shaderow?
	5. 
	Shadery sa rejestrowane w klasie GLS::GL_GPUResourceTracker
*/