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
#include "GL_Transform.h"

namespace GLS{
	class GL_GeometryManager;
	class GL_Shape;

    class GL_Mesh:public GL_Component{
		GLS::GL_Transform _localTransform;
		GLS::GL_Shape*_meshGeometry;

		GLboolean _renderEnable;
		GLenum _renderMode;
		glm::vec4 _color;
	public:
        GL_Mesh(std::string meshType,glm::vec3 location=glm::vec3(0.0f), glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f));
        GL_Mesh(GLuint vertN,glm::vec3 location=glm::vec3(0.0f), glm::vec3 rotation=glm::vec3(0.0f),glm::vec3 scale=glm::vec3(1.0f));
		~GL_Mesh();

		glm::vec3 getLocalLocation()const;
		glm::vec3 getLocalRotation()const;
		glm::vec3 getLocalScale()const;

		void setLocalLocation(glm::vec3 location);
		void setLocalRotation(glm::vec3 rotation);
		void setLocalScale(glm::vec3 scale);

		const GLS::GL_Shape*getGeometry()const;
		void changeGeometry(std::string meshType);
		void changeGeometry(GLuint vertN);

		GLboolean shouldRender()const;
		void enableRender();
		void disableRender();

		GLenum getRenderMode()const;
		void setRenderMode(GLenum renderMode);

		glm::vec4 getColor()const;
		void setColor(glm::vec4 color);
    };
}
/*
	Class used inside GL_GameObject class as the component

*/
