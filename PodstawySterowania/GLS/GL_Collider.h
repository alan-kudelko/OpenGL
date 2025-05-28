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
#include <vector>

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
		glm::vec2 _AABBvertices[4]{};
		glm::vec4 _renderColor; // For now
	public:
		GL_Collider(glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f),GLuint collisionGroup=1);
		virtual ~GL_Collider();

		GLuint getCollisionGroup()const;
		GLS::GL_Transform getLocalTransform()const;
		glm::vec2 getLocalLocation()const; // Will be erased, no need for it
		glm::vec3 getLocalRotation()const; // Will be erased, no need for it
		glm::vec2 getLocalScale()const;    // Will be erased, no need for it

		void setCollisionGroup(GLuint collisionGroup);
		void setLocalLocation(glm::vec2 location);
		void setLocalRotation(glm::vec3 rotation);
		void setLocalScale(glm::vec2 scale);

		glm::vec4 getRenderColor()const;
		void setRenderColor(glm::vec4 color);

		void enableCollisions();
		void disableCollisions();
		GLboolean shouldCollide()const; // Returns wheter collider should interact with other objects

		void getAABBvertices(glm::vec2* AABB)const; // Gets global location of AABB vertices
		void setAABBvertices(glm::vec2* AABB); // Sets global location of AABB vertices after transforms of GL_GameObject
		void setAABBvertices(std::vector<glm::vec2> AABB);
		// This way collision detection will be a bit faster than calculating position of AABB every frame
	};
	////////////////////////////////////////////////////////////////// GL_VertexCollider
	class GL_VertexCollider:public GL_Collider{
	protected:
		glm::vec2* _colliderVertices;
		GLuint _colliderVertCount;
		GLboolean _isConvex;
	public:
		GL_VertexCollider(glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f),GLuint collisionGroup=1);
		virtual ~GL_VertexCollider()=0;

		void getVertices(glm::vec2* vertices)const;
		GLuint getVertCount()const;
	};
	////////////////////////////////////////////////////////////////// GL_BoxCollider
	class GL_BoxCollider:public GL_VertexCollider{
	public:
		GL_BoxCollider(glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f),GLuint collisionGroup=1);
		~GL_BoxCollider();

		void setVertices(glm::vec2* vertices);

		// In the future there should be interface for changing location of indivudals vertices
	};
	////////////////////////////////////////////////////////////////// GL_MeshCollider
	class GL_MeshCollider:public GL_VertexCollider{
	public:
		GL_MeshCollider(glm::vec2*vertices,GLuint vertCount,glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f),GLuint collisionGroup=1);
		~GL_MeshCollider();

		void setVertices(glm::vec2* vertices,GLuint vertCount);
	};
	////////////////////////////////////////////////////////////////// GL_SphereCollider
	class GL_SphereCollider:public GL_Collider{
		GLfloat* semiMajor;
		GLfloat* semiMinor; // Perhaps not needed as the GL_Transform component can store that
	public:
		GL_SphereCollider(glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f),GLuint collisionGroup=1);
		~GL_SphereCollider();
		
	};
}

