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

