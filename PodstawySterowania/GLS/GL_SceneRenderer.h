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

		glm::mat4 _projection;
		//For now let's assume camera is immobile
	public:
		GL_SceneRenderer(glm::mat4 projection);
		~GL_SceneRenderer();

		glm::mat4 getProjectionMatrix()const;

		void setProjectionMatrix(glm::mat4 projection);

		void renderObject(const GLS::GL_GameObject&gameObject)const;
		void renderScene(const std::vector<GLS::GL_GameObject*>& sceneObjects)const;
	};
}

