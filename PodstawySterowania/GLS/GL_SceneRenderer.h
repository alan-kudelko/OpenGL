/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_SceneRenderer
 * -----------------------
 * Responsible for rendering game objects in a 2D/3D scene using OpenGL.
 * Manages projection matrix state and dispatches draw calls to render scene objects
 * including optional debug colliders.
 *
 * Core Features:
 * - Scene-wide orthographic or perspective projection matrix management
 * - Rendering of both visual geometry and optional collider overlays
 * - Efficient rendering of containers with scene objects (batched or sequential)
 *
 * Connects high-level scene management (GL_SceneManager, GL_GameObject)
 * with low-level OpenGL drawing logic.
 *
 * Intended as a modular rendering backend, enabling custom rendering logic,
 * debug visualization, and dynamic scene composition.
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

