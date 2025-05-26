/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_GameObject
 * -------------------
 * Core class representing a single entity within the game world.
 * Acts as a container for various components (e.g., GL_Transform, GL_Mesh, GL_Shader, GL_Collider, GL_CollisionBehaviour),
 * providing centralized access to behavior, rendering, and collision functionality.
 *
 * Stores metadata such as object name and destruction state.
 * Manages object-level logic, including position updates, rendering flags,
 * and interactions between components.
 *
 * Intended to serve as a flexible and extensible unit that can be composed
 * of shared or unique components, supporting a modular component-based architecture.
 */

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
	class GL_PhysicsBody;
	class GL_GameObject{
		static GLuint _GL_GameObjectCounter; // Counter of existing GL_GameObjects, used for debugging and for generating default names
		std::string _name; // Some kind of identifier to differentiate created objects
		GLboolean _shouldDestroy; // Flag indicating if object should be destroyed after event

		// Class will not own all components as they may be shared across multiple object instances
		GL_Transform*_transformComponent; // Used for creation of new GL_Transform component
		GL_Mesh*_meshComponent; // Pointer to existing GL_SHAPE component
		GL_Shader*_shaderComponent; // Pointer to existing GL_SHADER component
		GL_Collider*_colliderComponent; // Used for creation of new collider component for use in the class
		GL_PhysicsBody*_physicsComponent; // Used for creation of new physics body
		GL_CollisionBehaviour*_collisionBehaviourComponent; // Used for creation of new behaviour after collision
		//GL_TEXTURE*_textureComponentPtr;
		//GL_INPUT_CONTROLLER*_inputControllerComponentPtr;
		public:
		////////////////////////////////////////////////////////////////// GL_GameObject interface
		GL_GameObject(GLS::GL_Shader*shaderComponent,std::string meshType="rectangle",glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f));
		GL_GameObject(GLS::GL_Shader* shaderComponent,GLuint polygonCount=3,glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f));
		// Another default constructor creating empty object (without any components)
		GL_GameObject();

		~GL_GameObject();
		////////////////////////////////////////////////////////////////// GL_Transform interface
		glm::vec2 getLocation()const; // Returns current GL_GameObject location
		glm::vec3 getRotation()const; // Returns current GL_GameObject rotation
		glm::vec2 getScale()const; // Returns current GL_GameObject scale
		void setLocation(glm::vec2 location); // Sets current GL_GameObject location
		void setRotation(glm::vec3 rotation); // Sets current GL_GameObject rotation
		void setScale(glm::vec2 scale); // Sets current GL_GameObject scale
		void move(glm::vec2 delta); // Method for incrementing location coordinates
		void rotate(glm::vec3 delta); // Method for incrementing rotation coordinates
		void scaleBy(glm::vec2 delta); // Method for incrementing scale
		////////////////////////////////////////////////////////////////// GL_Physics interface (in near future)
		glm::vec2 getGameObjectLinearVelocity()const;
		glm::vec3 getGameObjectAngularVelocity()const;

		void setGameObjectLinearVelocity(glm::vec2 gameObjectLinearVelocity); // Sets current GL_GameObject linear velocity
		void setGameObjectAngularVelocity(glm::vec3 gameObjectRotationalVelocity); // Sets current GL_GameObject linear velocity
		void updateGameObjectLocation(GLfloat deltaTime); // updates game object's location and rotation according to velocities and deltaTime
		void markForDestruction(); // Method for marking the object to be destroyed by GL_SceneManager
		void unmarkForDestruction(); // Method for unmarking the object to be destroyed by GL_SceneManager
		GLboolean shouldDestroy()const; // Method returning if the object should be destroyed

		////////////////////////////////////////////////////////////////// GL_Shape interface
		void enableRender(); // Enables rendering on screen
		void disableRender(); // Disables rendering on screen
		GLboolean shouldRender()const; // Returns whether object is enabled for rendering on screen
		////////////////////////////////////////////////////////////////// GL_Collider interface
		void _recalculateAABB(); // Recalculates AABB vertices if GL_GameObject if transformed
		void enableCollisions(); // Enables collisions
		void disableCollisions(); // Disables collisions
		GLboolean shouldCollide()const; // Returns whether object should be able to collide with other objects
		////////////////////////////////////////////////////////////////// GL_CollisionBehaviour interface

		////////////////////////////////////////////////////////////////// GL_GameObject interface for component management
		GLS::GL_Transform*getTransformComponent();
		GLS::GL_Mesh*getMeshComponent();
		const GLS::GL_Shader*getShaderComponent()const;
		GLS::GL_Collider*getColliderComponent();
		GLS::GL_CollisionBehaviour*getCollisionBehaviourComponent();

		void createTransformComponent(glm::vec2 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f));
		void createMeshComponent(std::string meshType,glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f), glm::vec2 scale=glm::vec2(1.0f));
		void assignShaderComponent(GLS::GL_Shader*component);
		void createCollisionComponent(glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f),std::string colliderType="BoxCollider",GLuint collisionGroup=1); // May be overloaded in the future
		void createCollisionBehaviourComponent(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)=&GLS::behaviourDestroyAfterCollision);
	};
}
