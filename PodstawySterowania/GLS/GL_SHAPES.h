#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <iostream>

#include "GL_GPUResourceTracker.h"
extern GLS::GL_GPUResourceTracker GL_GPUresourceTracker;
namespace GLS{
    class GL_SHAPE{
	protected:
        std::string _name;
		GLenum _memoryLocation;
        GLuint _VAO;
        GLuint _VBO;
		GLuint _shaderProgram;
		GLfloat*_vertices;
		GLuint _vertN;
    public:
        GL_SHAPE(std::string name="brak",GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
        virtual ~GL_SHAPE();

        virtual void GLdrawShape(GLFWwindow*window)=0;
		std::string GLgetName()const;
		GLenum GLgetMemoryLocation()const;
		GLuint GLgetVAO()const;
		GLuint GLgetVBO()const;
		GLuint GLgetShader()const;
        GLfloat*GLgetVertices()const;
    };
	class GL_TRIANGLE:public GL_SHAPE{
		public:
		GL_TRIANGLE(GLfloat*vertices,std::string name,GLuint shaderProgram,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		~GL_TRIANGLE();
		void GLdrawShape(GLFWwindow*window)override;
	};
	class GL_RECTANGLE:public GL_SHAPE{
		GLuint _EBO;
		GLuint _indices[6]{1,2,3,0,1,3};
		public:
        GL_RECTANGLE(GLfloat*vertices=nullptr,std::string name="brak",GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
        ~GL_RECTANGLE();

		void GLdrawShape(GLFWwindow*window);
	};
}
