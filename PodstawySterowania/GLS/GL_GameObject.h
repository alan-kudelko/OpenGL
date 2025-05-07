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
	class GL_GameObject{
		std::string _name;
		glm::vec3 _location;
		glm::vec3 _rotation;
		GL_SHAPE*shapeComponent;
		GL_SHADER*shaderComponentPtr;
		//GL_TEXTURE*textureComponentPtr;
		//GL_INPUT_CONTROLLER*inputControllerComponentPtr;
		
		public:
		GL_GameObject(glm::vec3 location={},glm::vec3 rotation={},std::string name="Default");
		~GL_GameObject();
		
		glm::vec3 getLocation()const;
		glm::vec3 getRotation()const;
		
		const GL_Component&getComponent()const;
		
		glm::vec3 setLocation(glm::vec3 location);
		glm::vec3 setRotation(glm::vec3 rotation);
		
		GL_Component&setComponent()const;
		
		GL_Component*createComponent(); // Returns pointer to created component in order to configure it
	};
}