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
#include "GL_SHAPES.h"
#include "GL_SHADER.h"

namespace GLS{
	class GL_GameObject{
		std::string _name;
		glm::vec3 _location;
		glm::vec3 _rotation;
		GL_SHAPE*_shapeComponent;
		GL_SHADER*_shaderComponentPtr;
		//GL_TEXTURE*_textureComponentPtr;
		//GL_INPUT_CONTROLLER*_inputControllerComponentPtr;
		//GL_COLIDER*_coliderComponent;
		public:
		GL_GameObject(glm::vec3 location={},glm::vec3 rotation={},std::string name="Default");
		~GL_GameObject();

		glm::vec3 getLocation()const;
		glm::vec3 getRotation()const;

		const GLS::GL_Component&getComponent(GLS::GL_Component componentType)const;

		glm::vec3 setLocation(glm::vec3 location);
		glm::vec3 setRotation(glm::vec3 rotation);

		GLS::GL_Component&setComponent(GLS::GL_Component componentType)const;

		GLS::GL_Component*createComponent(GLS::GL_Component componentType); // Returns pointer to created component in order to configure it
	};
}
