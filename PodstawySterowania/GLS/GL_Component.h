#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLS{
	// Base class for all avaible GL_GameObject components
	class GL_Component{
		public:
		GL_Component(){};
		virtual~GL_Component()=default;
	};
}