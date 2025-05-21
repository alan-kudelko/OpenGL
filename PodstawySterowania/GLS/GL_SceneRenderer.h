/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_SceneRenderer
 * -----------------------
 * Responsible for rendering game objects in a 3D scene using OpenGL.
 * Handles projection matrix setup and provides methods for drawing individual
 * objects as well as full scenes.
 *
 * Core Features:
 * - Scene-wide projection matrix management
 * - Rendering of both standard geometry and debug colliders (toggleable)
 * - Efficient rendering of scene object containers
 *
 * Intended to be used as a rendering backend that connects scene management
 * (GL_SceneManager) with low-level OpenGL draw calls.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLS{
	class GL_GameObject;

	class GL_SceneRenderer{
		GLboolean _renderCollider;
		glm::mat4 _projection;
		void renderCollider(GLS::GL_GameObject& gameObject); // Render collider
	public:
		GL_SceneRenderer(glm::mat4 projection); // Projection of a scene
		~GL_SceneRenderer();

		glm::mat4 getProjection()const; // Returns current projection

		void setProjectionMatrix(glm::mat4 projection); // Sets current projection

		void renderObject(GLS::GL_GameObject&gameObject); // Render single scene object
		void renderScene(std::vector<GLS::GL_GameObject*>& sceneObjects); // Render all scene objects in the vector container
	};
}

