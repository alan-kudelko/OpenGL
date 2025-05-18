#pragma once

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GL_PhysicsBody.h"
#include "GL_CollisionManager.h"

namespace GLS{
	class GL_PhysicsManager;
	class GL_CollisionResolve{
		
		
	public:
		GL_CollisionResolve();
		~GL_CollisionResolve();
		
		void resolveCollision(GLS::GL_CollisionInfo collisionInfo);
    };
}
