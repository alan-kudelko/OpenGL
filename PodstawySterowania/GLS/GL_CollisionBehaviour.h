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
	// For sure there should be some kind of interface to generate collider based on geometry of an object
	// Another possibilities are simple prefabs like triangle or polygon
	// GL_Collider should contain size, location and rotation of collision box
	// Maybe size isn't a good idea, I think it should be more generalized
	// Good idea is to add collisions groups to optimize collision detection
	// Additionally I will use two stage collision detection algorithm utilizing bounding box for broad phase and some fancier algorithm for narrow phase
	// Collision handling will be processed by class GL_CollisionManager

	class GL_CollisionBehaviour{
		GLuint _collisionGroup;
		glm::vec3 _boundingBoxLocation;
		glm::vec3 _originalBoundingBoxSize;
		glm::vec3 _transformedBoundingBoxSize;
	public:
		GL_Collider(glm::vec3 boundingBoxLocation={0.0f,0.0f,0.0f},glm::vec3 boundingBoxSize={1.0f,1.0f,1.0f},GLuint collisionGroup=1);
		~GL_Collider();

		GLuint getCollisionGroup()const;
		glm::vec3 getBoundingBoxLocation()const;
		glm::vec3 getBoundingBoxSize()const;
		
		glm::vec3 getBoundingBoxMin()const; // Used by GL_ColliderManager only
		glm::vec3 getBoundingBoxMax()const; // Same

		void setCollisionGroup(GLuint collisionGroup);
		void setBoundingBoxLocation(glm::vec3 boundingBoxLocation);
		void setBoundingBoxSize(glm::vec3 boundingBoxSize);
		
		void updateBoundingBoxSize(glm::vec3 rotation); // Used to recalculate bounding box dimensions after rotation
	};
}

