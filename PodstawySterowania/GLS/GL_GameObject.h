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
#include "GL_Shape.h"
#include "GL_Shader.h"
#include "GL_Collider.h"

namespace GLS{
	enum GL_ComponentType{GL_SHAPE_Component=1,GL_SHADER_Component=2,GL_COLLIDER_Component=3}; // Enum to indicate component we want to get pointer to
	class GL_GameObject{
		std::string _name; // Some kind of identifier to differentiate created objects
		GLboolean _renderEnable;
		GLboolean _collisionEnable;
		glm::vec3 _gameObjectLocation; // Location of GL_GameObject object in 2D/3D world
		glm::vec3 _gameObjectRotation; // Rotation of GL_GameObject object in 2D/3D world

		glm::vec3*_shapeComponentLocation; // Location of GL_SHAPE component object relative to GL_GameObject
		glm::vec3*_shapeComponentRotation; // Rotation of GL_SHAPE component object relative to GL_GameObject
		glm::vec3*_shapeComponentScale; // Scale of GL_SHAPE component object relative to GL_GameObject

		glm::mat4 _model;
		// Class will not own all components as they may be shared across multiple object instances 
		GL_Shape*_shapeComponentPtr; // Pointer to existing GL_SHAPE component
		GL_Shader*_shaderComponentPtr; // Pointer to existing GL_SHADER component
		GL_Collider*_colliderComponentPtr; // Used for creation of new collider component for use in the class
		//GL_TEXTURE*_textureComponentPtr;
		//GL_INPUT_CONTROLLER*_inputControllerComponentPtr;
		// Pointer for function called upon detected collisions
		// There should be possibility to attach your own functions
		// Of course function should have the same signature
		// Maybe class of "after collision" behaviours?
		void _updateColliderBoundingBox(glm::vec3 size);
		public:
		GL_GameObject(glm::vec3 location={},glm::vec3 rotation={},std::string name="Default");
		~GL_GameObject();

		glm::vec3 getGameObjectLocation()const; // Returns current GL_GameObject location
		glm::vec3 getGameObjectRotation()const; // Returns current GL_GameObject rotation

		glm::vec3 getShapeComponentLocation()const; // Returns current GL_SHAPE component location
		glm::vec3 getShapeComponentRotation()const; // Returns current GL_SHAPE component rotation
		glm::vec3 getShapeComponentScale()const; // Returns current GL_SHAPE component scale

		void setGameObjectLocation(glm::vec3 gameObjectLocation); // Sets current GL_GameObject location
		void setGameObjectRotation(glm::vec3 gameObjectRotation); // Sets current GL_GameObject rotation

		void updateGameObjectLocation(glm::vec3 gameObjectLocation); // Method for incrementing location coordinates
		void updateGameObjectRotation(glm::vec3 gameObjectRotation); // Method for incrementing rotation coordinates

		void setShapeComponentLocation(glm::vec3 shapeComponentLocation); // Sets current GL_SHAPE component location
		void setShapeComponentRotation(glm::vec3 shapeComponentRotation); // Sets current GL_SHAPE component rotation
		void setShapeComponentSize(glm::vec3 shapeComponentScale); // Sets current GL_SHAPE component scale
		
		void setColliderComponentLocation(glm::vec3 location)const; // Sets relative offset of GL_Collider
		void setColliderComponentSize(glm::vec3 size)const; // Sets size of GL_Collider component

		GLboolean shouldRender()const; // Returns whether object is enabled for rendering on screen
		void enableRender(); // Enables rendering on screen
		void disableRender(); // Disables rendering on screen
		
		GLboolean shouldCollide()const; // Returns whether object should be able to collide with other objects
		void enableCollisions(); // Enables collisions
		void disableCollisions(); // Disables collisions

		// For now I assumed that there will be only one component of each component type avaible
		
		const GLS::GL_Shape*getShapeComponent()const;
		const GLS::GL_Shader*getShaderComponent()const;
		const GLS::GL_Collider*getColliderComponent()const;
		
		void assignShapeComponent(GLS::GL_Shape*component);
		void assignShaderComponent(GLS::GL_Shader*component);
		void createCollisionComponent(glm::vec3 location,glm::vec3 size,GLuint collisionGroup=1); // May be overloaded in the future
	};
}
