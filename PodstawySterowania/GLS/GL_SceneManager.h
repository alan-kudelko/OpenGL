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