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
	class GL_GameObject;
	// Simple temporary class for managing after collision actions
	void behaviourDestroyAfterCollision(GLS::GL_GameObject*gameObject);

	class GL_CollisionBehaviour:public GLS::GL_Component{
		GLboolean _behaviourActive;
		void (*_behaviourFunPtr)(GLS::GL_GameObject*);
	public:
		GL_CollisionBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*)=nullptr);
		~GL_CollisionBehaviour();

		void addBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*));
		void callBehaviour(GLS::GL_GameObject*gameObject);

		void enableBehaviour();
		void disableBehaviour();
		GLboolean behaviourActive()const;
	};
}
