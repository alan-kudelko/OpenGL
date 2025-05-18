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
	// For sure there should be some kind of interface to generate collider based on geometry of an object
	// Another possibilities are simple prefabs like triangle or polygon
	// GL_Collider should contain size, location and rotation of collision box
	// Maybe size isn't a good idea, I think it should be more generalized
	// Good idea is to add collisions groups to optimize collision detection
	// Additionally I will use two stage collision detection algorithm utilizing bounding box for broad phase and some fancier algorithm for narrow phase
	// Collision handling will be processed by class GL_CollisionManager
	class GL_GameObject;
	struct GL_CollisionInfo{
		GLS::GL_GameObject *obj1;
		GLS::GL_GameObject *obj2;
		glm::vec3 contactPoint;
		glm::vec3 normalVector;
		GLfloat penetrationDepth;
		// In the future collision time
	};
	class GL_CollisionManager{
		GLboolean _checkAABBCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2);
	public:
		GL_CollisionManager();
		~GL_CollisionManager();

		std::vector<GL_CollisionInfo>checkCollisions(std::vector<GLS::GL_GameObject*>gameObjects);
	};
}
