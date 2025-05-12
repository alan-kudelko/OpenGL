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


namespace GLS{
	class GL_SceneManager{
		// Container for all scene objects
	public:
		GL_SceneManager();
		~GL_SceneManager();
		
	};
}

