#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_Component.h"

namespace GLS{
	class GL_Script:public GL_Component{
		std::string _scriptName;
		void*_scriptPtr;
		GLboolean _shouldExecute;
	public:
		GL_Script(std::string scriptName,scriptrPtr=nullptr);
		~GL_Script();

		void executeScript();
		void enableExecution();
		void disableExecution();
		GLboolean shouldExecute()const;
		
	};
}
