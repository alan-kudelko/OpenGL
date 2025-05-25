/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_Mesh
 * -------------
 * Component representing a renderable 3D mesh object within the scene.
 * Encapsulates local transformation data (position, rotation, scale) and
 * a reference to its geometric shape (GL_Shape).
 *
 * Provides methods to modify transformation parameters, switch geometry dynamically,
 * control rendering state, and customize appearance (color, render mode).
 *
 * Intended to be used as a core visual representation of a game object,
 * supporting both primitive-based shapes and procedurally generated geometry.
 */

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
		glm::vec2* _vertices;
	public:
        GL_Mesh(std::string meshType,glm::vec2 location=glm::vec2(0.0f), glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f));
        GL_Mesh(GLuint vertN,glm::vec2 location=glm::vec2(0.0f), glm::vec3 rotation=glm::vec3(0.0f),glm::vec2 scale=glm::vec2(1.0f));
		~GL_Mesh();

		glm::vec2 getLocalLocation()const;
		glm::vec3 getLocalRotation()const;
		glm::vec2 getLocalScale()const;

		void setLocalLocation(glm::vec2 location);
		void setLocalRotation(glm::vec3 rotation);
		void setLocalScale(glm::vec2 scale);

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

		glm::vec2*getVertices()const;
    };
}
