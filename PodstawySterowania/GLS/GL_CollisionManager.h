/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_CollisionManager
 * -------------------------
 * Handles collision detection between scene objects using an Axis-Aligned Bounding Box (AABB) algorithm.
 * Designed to support a two-phase collision detection strategy:
 * - Broad Phase: AABB intersection checks for early elimination
 * - Narrow Phase: Placeholder for more accurate future methods (e.g. SAT, GJK)
 *
 * Class provides:
 * - `checkCollisions()`: returns a list of detected collisions with contact data
 * - Internal AABB overlap check via `_checkAABBCollision()`
 *
 * Struct GL_CollisionInfo
 * -----------------------
 * Represents a single collision event:
 * - Pointers to the two involved objects
 * - Contact point, normal vector, and penetration depth
 * - Extendable to include collision time for continuous physics simulation
 *
 * Integration:
 * Designed to be used by GL_SceneManager and GL_GameObject systems.
 * Can trigger responses via GL_CollisionBehaviour.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLS{
	class GL_GameObject;
	struct GL_CollisionInfo{
		GLS::GL_GameObject *obj1;
		GLS::GL_GameObject *obj2;
		glm::vec2 contactPoint;
		glm::vec2 normalVector;
		GLfloat penetrationDepth;
		// In the future collision time
	};
	class GL_CollisionManager{
		GLboolean _checkAABBCollision(glm::vec2 obj1BoundingBoxMin,glm::vec2 obj1BoundingBoxMax,glm::vec2 obj2BoundingBoxMin,glm::vec2 obj2BoundingBoxMax);
		GLboolean _checkSATCollision(glm::vec2*obj1Vertices,GLuint obj1VertCount,glm::vec2*obj2Vertices,GLuint obj2VertCount);
	public:
		GL_CollisionManager();
		~GL_CollisionManager();

		std::vector<GL_CollisionInfo>checkCollisions(std::vector<GLS::GL_GameObject*>gameObjects);
	};
}
