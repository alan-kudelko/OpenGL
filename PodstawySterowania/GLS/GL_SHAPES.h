#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <iostream>

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
        GL_SHAPE(GLfloat*vertices=nullptr,GLuint vertN=0,std::string name="brak",GLuint shaderProgram=0,GLuint VAO=0,GLuint VBO=0,GLenum memoryLocation=GL_STATIC_DRAW);
        virtual ~GL_SHAPE();

        virtual void GL_drawShape(GLFWwindow*window)=0;
		std::string GL_getName()const;
		GLenum GL_getMemoryLocation()const;
		GLuint GL_getVAO()const;
		GLuint GL_getVBO()const;
		GLuint GL_getShader()const;
        GLfloat*GL_getVertices()const;
    };
	class GL_TRIANGLE:public GL_SHAPE{
		public:
		GL_TRIANGLE(GLfloat*vertices,GLuint vertN,std::string name,GLuint shaderProgram,GLuint VAO,GLuint VBO,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		~GL_TRIANGLE();
		void GL_drawShape(GLFWwindow*window)override;
	};
	class GL_RECTANGLE:public GL_SHAPE{
		GLuint _EBO;
		GLuint _indices[6]{1,2,3,0,1,3};
		public:
        GL_RECTANGLE(GLfloat*vertices=nullptr,GLuint vertN=0,std::string name="brak",GLuint shaderProgram=0,GLuint VAO=0,GLuint VBO=0,GLenum memoryLocation=GL_STATIC_DRAW);
        ~GL_RECTANGLE();

		void GL_drawShape(GLFWwindow*window);
	};
}
