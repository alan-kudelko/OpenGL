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

#include "GL_GameObject.h"


namespace GLS{
	class GL_SceneManager{
		// Container for all scene objects
		// For now it works, code needs to be refactorized
		// but this concept works
		std::vector<GLS::GL_GameObject*>_sceneObjects;
	public:
		GL_SceneManager();
		~GL_SceneManager();

		void addNewGameObject(GLS::GL_GameObject*gameObject);
		const std::vector<GLS::GL_GameObject*>&getSceneObjects()const;
		GL_GameObject*getSceneObject(GLuint it);
		GLuint getSceneObjectNumber()const; // Returns number of scene objects
		
		void clearScene(); // Removes all object from the scene
		void updateScene(); // Checks if object should be destroyed after event for instance - collision
	};
}

