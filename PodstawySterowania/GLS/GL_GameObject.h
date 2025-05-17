#pragma once

#include <glad/glad.h>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_CollisionBehaviour.h"

namespace GLS{
	class GL_Transform;
	class GL_Mesh;
	class GL_Shader;
	class GL_Collider;
	class GL_GameObject{
		static GLuint _GL_GameObjectCounter; // Counter of existing GL_GameObjects, used for debugging and for generating default names
		std::string _name; // Some kind of identifier to differentiate created objects
		GLboolean _shouldDestroy; // Flag indicating if object should be destroyed after event

		glm::vec3 _gameObjectLinearVelocity; // Linear velocity of GL_GameObject in 2D/3D world
		glm::vec3 _gameObjectRotationalVelocity; // Rotational velocity of GL_GameObject in 2D/3D world
		// Velocities will be moved to GL_Physics or GL_RigidBody class

		// class GL_Shape has to be changed to move this variables to another component class
		glm::vec3*_shapeComponentLocation; // Location of GL_SHAPE component object relative to GL_GameObject
		glm::vec3*_shapeComponentRotation; // Rotation of GL_SHAPE component object relative to GL_GameObject
		glm::vec3*_shapeComponentScale; // Scale of GL_SHAPE component object relative to GL_GameObject

		// Class will not own all components as they may be shared across multiple object instances
		GL_Transform*_transformComponent; // Used for creation of new GL_Transform component
		GL_Mesh*_meshComponent; // Pointer to existing GL_SHAPE component
		GL_Shader*_shaderComponent; // Pointer to existing GL_SHADER component
		GL_Collider*_colliderComponent; // Used for creation of new collider component for use in the class
		GL_CollisionBehaviour*_collisionBehaviourComponent; // Used for creation of new behaviour after collision
		//GL_Physics Used for creation of new GL_Physics component for use in the class
		//GL_TEXTURE*_textureComponentPtr;
		//GL_INPUT_CONTROLLER*_inputControllerComponentPtr;
		public:
		////////////////////////////////////////////////////////////////// GL_GameObject interface
		// New default constructor
		// Creates new GL_Transform component with given parameters
		// Creates new GL_Mesh existing geometry to GL_Shape (triangle, rectangle, pentagon etc.)
		// Initializes GL_Shader with existing shader
		// Creates new GL_Collider with given parameters and collision group 1
		// Creates new GL_CollisionBehavior component with default behaviour
		GL_GameObject(GLS::GL_Shader*shaderComponent,std::string meshType="rectangle",glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f));
		// Another default constructor creating empty object (without any components)
		GL_GameObject();

		~GL_GameObject();
		////////////////////////////////////////////////////////////////// GL_Transform interface
		glm::vec3 getLocation()const; // Returns current GL_GameObject location
		glm::vec3 getRotation()const; // Returns current GL_GameObject rotation
		glm::vec3 getScale()const; // Returns current GL_GameObject scale
		void setLocation(glm::vec3 location); // Sets current GL_GameObject location
		void setRotation(glm::vec3 rotation); // Sets current GL_GameObject rotation
		void setScale(glm::vec3 scale); // Sets current GL_GameObject scale
		void move(glm::vec3 delta); // Method for incrementing location coordinates (will be erased in the future or moved to private)
		void rotate(glm::vec3 delta); // Method for incrementing rotation coordinates
		////////////////////////////////////////////////////////////////// GL_Physics interface (in near future)
		glm::vec3 getGameObjectLinearVelocity()const;
		glm::vec3 getGameObjectRotationalVelocity()const;

		void setGameObjectLinearVelocity(glm::vec3 gameObjectLinearVelocity); // Sets current GL_GameObject linear velocity
		void setGameObjectRotationalVelocity(glm::vec3 gameObjectRotationalVelocity); // Sets current GL_GameObject linear velocity
		void updateGameObjectLocation(GLfloat deltaTime); // updates game object's location and rotation according to velocities and deltaTime
		void markForDestruction(); // Method for marking the object to be destroyed by GL_SceneManager
		void unmarkForDestruction(); // Method for unmarking the object to be destroyed by GL_SceneManager
		GLboolean shouldDestroy()const; // Method returning if the object should be destroyed

		////////////////////////////////////////////////////////////////// GL_Shape interface
		void enableRender(); // Enables rendering on screen
		void disableRender(); // Disables rendering on screen
		GLboolean shouldRender()const; // Returns whether object is enabled for rendering on screen
		////////////////////////////////////////////////////////////////// GL_Collider interface
		void enableCollisions(); // Enables collisions
		void disableCollisions(); // Disables collisions
		GLboolean shouldCollide()const; // Returns whether object should be able to collide with other objects
		////////////////////////////////////////////////////////////////// GL_CollisionBehaviour interface

		////////////////////////////////////////////////////////////////// GL_GameObject interface for component management
		GLS::GL_Transform*getTransformComponent()const;
		GLS::GL_Mesh*getMeshComponent()const;
		const GLS::GL_Shader*getShaderComponent()const;
		GLS::GL_Collider*getColliderComponent()const;
		GLS::GL_CollisionBehaviour*getCollisionBehaviourComponent();

		void createTransformComponent(glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f));
		void createMeshComponent(std::string meshType,glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f), glm::vec3 scale=glm::vec3(1.0f));
		void assignShaderComponent(GLS::GL_Shader*component);
		void createCollisionComponent(glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 size=glm::vec3(1.0f),GLuint collisionGroup=1); // May be overloaded in the future
		void createCollisionBehaviourComponent(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)=&GLS::behaviourDestroyAfterCollision);
	};
}
/*
 * Class GL_GameObject
 * -------------------
 * Core class representing a single entity within the game world.
 * Acts as a container for various components (e.g., GL_Transform, GL_Mesh, GL_Shader, GL_Collider, GL_ColliderBehaviour),
 * providing centralized access to behavior, rendering, and collision functionality.
 * 
 * Stores metadata such as object name and destruction state.
 * Manages object-level logic, including position updates, rendering flags,
 * and interactions between components.
 * 
 * Intended to serve as a flexible and extensible unit that can be composed
 * of shared or unique components, supporting a modular component-based architecture.
 */