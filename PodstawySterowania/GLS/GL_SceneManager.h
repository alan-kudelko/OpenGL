/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_SceneManager
 * ----------------------
 * High-level manager responsible for storing and updating game objects in a scene.
 *
 * Maintains a list of pointers to GL_GameObject instances representing entities in the 3D scene.
 * Provides methods for adding, accessing, and managing the lifecycle of scene objects.
 *
 * Core Features:
 * - Immutable and mutable access to stored objects
 * - Scene clearing and reset support
 * - Object update routine (e.g., post-collision cleanup)
 *
 * Intended as the central point of control for organizing runtime game entities
 * and handling their logical grouping and updates.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLS{
	class GL_GameObject;
	
	class GL_SceneManager{
		std::vector<GLS::GL_GameObject*>_sceneObjects;
	public:
		GL_SceneManager();
		~GL_SceneManager();

		void addNewGameObject(GLS::GL_GameObject*gameObject);
		const std::vector<GLS::GL_GameObject*>&getSceneObjectsConst()const;
		std::vector<GLS::GL_GameObject*>&getSceneObjectsMutable();
		
		const GL_GameObject&getSceneObjectConst(GLuint n)const;
		GL_GameObject&getSceneObjectMutable(GLuint n);
		GLuint getSceneObjectNumber()const; // Returns number of scene objects
		
		void clearScene(); // Removes all object from the scene
		void updateScene(GLuint offset=0); // Iterates through objects and checks if any object should be destroyed after event for instance - collision
	};
}