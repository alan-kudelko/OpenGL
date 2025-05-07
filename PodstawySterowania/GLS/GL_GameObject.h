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
	enum GL_ComponentType{GL_SHAPE_Component=1,GL_SHADER_Component=2};
	class GL_GameObject{
		std::string _name;
		glm::vec3 _gameObjectLocation;
		glm::vec3 _gameObjectRotation;
		
		glm::vec3*_shapeComponentLocation;
		glm::vec3*_shapeComponentRotation;
		glm::vec3*_shapeComponentScale;
		
		GL_SHAPE*_shapeComponentPtr;
		GL_SHADER*_shaderComponentPtr;
		//GL_TEXTURE*_textureComponentPtr;
		//GL_INPUT_CONTROLLER*_inputControllerComponentPtr;
		//GL_COLIDER*_coliderComponent;
		public:
		GL_GameObject(glm::vec3 location={},glm::vec3 rotation={},std::string name="Default");
		~GL_GameObject();

		glm::vec3 getGameObjectLocation()const;
		glm::vec3 getGameObjectRotation()const;
		
		glm::vec3 getShapeComponentLocation()const;
		glm::vec3 getShapeComponentRotation()const;
		glm::vec3 getShapeComponentScale()const;
		
		void setGameObjectLocation(glm::vec3 gameObjectLocation);
		void setGameObjectRotation(glm::vec3 gameObjectRotation);
		
		void updateGameObjectLocation(glm::vec3 gameObjectLocation);
		void updateGameObjectRotation(glm::vec3 gameObjectRotation);
		
		void setShapeComponentLocation(glm::vec3 shapeComponentLocation);
		void setShapeComponentRotation(glm::vec3 shapeComponentRotation);
		void setShapeComponentScale(glm::vec3 shapeComponentScale);
		
		const GLS::GL_Component*getComponent(GLS::GL_Component componentType)const;

		GLS::GL_Component&setComponent(GLS::GL_Component componentType)const;
		
		void addComponent(GLS::GL_Component*componentType); // Returns pointer to created component in order to configure it
		void renderObject()const;
	};
}
