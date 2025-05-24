/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_Collider
 * ------------------
 * Component representing an object's collision properties in 3D space.
 * Manages local transformation, collision group assignment, and bounding box recalculations.
 *
 * Core Features:
 * - Local transform-based bounding box (axis-aligned)
 * - Dynamic bounding box recalculation based on rotation
 * - Collision group filtering for broad-phase optimization
 * - Toggleable collision participation per object
 *
 * Intended as a base class for future extensions such as:
 * - Geometry-based collider generation
 * - Support for custom shapes (e.g., spheres, polygons)
 * - Two-phase collision detection via GL_CollisionManager
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_Component.h"
#include "GL_Transform.h"

namespace GLS{
	// For sure there should be some kind of interface to generate collider based on geometry of an object but that will be for child classes
	// Another possibilities are simple prefabs like triangle or polygon
	// GL_Collider should contain size, location and rotation of collision box
	// Maybe size isn't a good idea, I think it should be more generalized
	// Good idea is to add collisions groups to optimize collision detection
	// Additionally I will use two stage collision detection algorithm utilizing bounding box for broad phase and some fancier algorithm for narrow phase
	// Collision handling will be processed by class GL_CollisionManager
	class GL_Collider:public GL_Component{
		GLboolean _collisionEnable;
		GLuint _collisionGroup;
		GLS::GL_Transform _localTransform;
		glm::vec3 _transformedScale; // Size needs to be recalculated after each rotation
	public:
		GL_Collider(glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f),GLuint collisionGroup=1);
		~GL_Collider();

		GLuint getCollisionGroup()const;
		glm::vec3 getLocalLocation()const;
		glm::vec3 getLocalRotation()const;
		glm::vec3 getLocalScale()const;

		glm::vec3 getBoundingBoxMin()const; // Used by GL_ColliderManager only
		glm::vec3 getBoundingBoxMax()const; // Same

		void setCollisionGroup(GLuint collisionGroup);
		void setLocalLocation(glm::vec3 location);
		void setLocalRotation(glm::vec3 rotation);
		void setLocalScale(glm::vec3 scale);

		void updateBoundingBoxSize(glm::vec3 rotation); // Used to recalculate bounding box dimensions after rotation
		void enableCollisions();
		void disableCollisions();
		GLboolean shouldCollide()const; // Returns wheter collider should interact with other objects
	};

	class GL_BoxCollider:public GL_Collider{
		glm::vec3*_boxVertices;
	public:
		GL_BoxCollider(glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f));
		~GL_BoxCollider();

		void getBoxVertices(glm::vec3*vertices)const;
		// In the future there should be interface for changing location of indivudals vertices
	};
	class GL_MeshCollider:public GL_Collider{
		glm::vec3* _meshVertices;
		GLboolean _isConvex; // Will be needed for triangulation
	public:
		GL_MeshCollider();
		~GL_MeshCollider();
	};
	class GL_SphereCollider:public GL_Collider{
	public:
		GL_SphereCollider(glm::vec3 location=glm::vec3(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f),GLuint collisionGroup=1);
		~GL_SphereCollider();
	};
	
}

