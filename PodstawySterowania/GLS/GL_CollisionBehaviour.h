/*
 * Author: Alan Kude�ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_CollisionBehaviour
 * ---------------------------
 * Component defining post-collision behavior for game objects.
 * Uses function pointers to allow modular and customizable responses to collisions.
 *
 * Built-in behaviors:
 * - behaviourDestroyAfterCollision: removes involved objects
 * - behaviourReverseVelocityAfterCollision: inverts velocity after contact
 * - behaviourDoNothing: explicitly ignores collisions
 *
 * Key Features:
 * - Dynamic assignment of behavior via function pointers
 * - Toggleable activation per object
 * - Compatible with GL_GameObject-based collision system
 *
 * Intended for use with a collision manager that calls `callBehaviour()` after collision detection.
 */

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
	class GL_GameObject;
	// Simple temporary class for managing after collision actions
	// Signatures have to match
	void behaviourDestroyAfterCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2);
	void behaviourReverseVelocityAfterCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2);
	void behaviourDoNothing(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2);

	class GL_CollisionBehaviour:public GLS::GL_Component{
		GLboolean _behaviourActive;
		void (*_behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*);
	public:
		GL_CollisionBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)=nullptr);
		~GL_CollisionBehaviour();

		void addBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*));
		void callBehaviour(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2);

		void enableBehaviour();
		void disableBehaviour();
		GLboolean behaviourActive()const;
	};
}
