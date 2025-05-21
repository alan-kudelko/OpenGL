/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_PhysicsBody
 * --------------------
 * Represents the physical properties and state of a game object within the simulation.
 * This component stores data such as mass, velocity, acceleration, and center of mass.
 *
 * Supports toggling physics and gravity individually, making it useful for both dynamic and static bodies.
 * It does not implement force integration directly, allowing flexibility for future physics systems.
 *
 * Intended to be attached to a GL_GameObject as a modular component in a component-based architecture.
 */

#pragma once

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_Component.h"

namespace GLS{
	class GL_PhysicsBody:public GLS::GL_Component{
		GLboolean _physicsActive;
		GLboolean _gravityActive;
		
		GLfloat _mass; // [kg]
		
		glm::vec3 _linearVelocity; // [m/s]
		glm::vec3 _angularVelocity; // [rad/s]
		
		glm::vec3 _linearAcceleration; // [m/s^2]
		glm::vec3 _angularAcceleration; // [rad/s^2]
		
		glm::vec3 _centerOffMass; // Center of mass offset [m]
	public:
		GL_PhysicsBody();
		~GL_PhysicsBody();
////////////////////////////////////////////////////////////////// Physics enable operations
		GLboolean isPhysicsActive()const;
		void enablePhysics();
		void disablePhysics();
////////////////////////////////////////////////////////////////// Gravity operations
		GLboolean isGravityActive()const;
		void enableGravity();
		void disableGravity();
////////////////////////////////////////////////////////////////// Mass operations
		GLfloat getMass()const;		
		void setMass(GLfloat mass);
////////////////////////////////////////////////////////////////// Linear velocity operations
		glm::vec3 getLinearVelocity()const;		
		void setLinearVelocity(glm::vec3 linearVelocity);
////////////////////////////////////////////////////////////////// Angular velocity operations
		glm::vec3 getAngularVelocity()const;		
		void setAngularVelocity(glm::vec3 angularVelocity);
////////////////////////////////////////////////////////////////// Linear acceleration operations
		glm::vec3 getLinearAcceleration()const;	
		void setLinearAcceleration(glm::vec3 linearAcceleration);
////////////////////////////////////////////////////////////////// Angular acceleration operations
		glm::vec3 getAngularAcceleration()const;	
		void setAngularAcceleration(glm::vec3 angularAcceleration);
    };
}
