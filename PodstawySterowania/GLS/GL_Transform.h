/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_Transform
 * ------------------
 * Component representing an object's transformation in 2D space with optional future extension to 3D.
 * Stores and manages local position (_location), rotation (_rotation), and scale (_scale).
 *
 * Core Features:
 * - Provides utility methods for translating, rotating, scaling and resetting the transform
 * - Rotation is stored as vec3 for forward compatibility with 3D transforms
 * - Includes static method to normalize angles to the range [0, 360) degrees
 *
 * Designed to be attached to any object requiring spatial representation:
 * - Game entities
 * - Colliders
 * - Renderable meshes
 *
 * Serves as the transformation base for object hierarchy, physics simulation and rendering calculations.
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
	class GL_Transform:public GL_Component{
		glm::vec2 _location;
		glm::vec3 _rotation; // Retained as glm::vec3 for future compability
		glm::vec2 _scale;
	public:
		static glm::vec3 normalizeAngles(glm::vec3 rotation); // Retained as glm::vec3 for future compability

		GL_Transform(glm::vec2 location=glm::vec2(0.0f),glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f));
		~GL_Transform();

		glm::vec2 getLocation()const;
		glm::vec3 getRotation()const;
		glm::vec2 getScale()const;

		void move(const glm::vec2&delta);
		void rotate(const glm::vec3&delta);
		void scaleBy(const glm::vec2&factor);

		void setLocation(const glm::vec2&location);
		void setRotation(const glm::vec3&rotation);
		void setScale(const glm::vec2&scale);

		void reset();
	};
}