/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_Transform
 * ------------------
 * Component representing an object's transformation in 3D space.
 * Stores and manages position (_location), rotation (_rotation), and scale (_scale).
 *
 * Provides methods to move, rotate, scale, and reset the transform.
 * Rotation angles are normalized to the range [0, 360) degrees.
 *
 * Intended to be used as a reusable component for any game object, mesh, collider or future objects yet to be implemented that requires transformations.
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