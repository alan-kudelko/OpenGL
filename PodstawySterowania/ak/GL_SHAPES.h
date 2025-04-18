#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <iostream>


namespace ak{

    class GL_SHAPE{
        std::string _name;
		GLenum _memoryLocation;
        GLuint _VAO;
        GLuint _VBO;
		GLuint _shaderProgram;
		GLfloat*_vertices;
		GLuint _vertN;
    public:
        GL_SHAPE(GLfloat*vertices,int vertN,std::string name,int shaderProgram,int VAO,int VBO,GLenum memoryLocation=GL_DYNAMIC_DRAW);
        ~GL_SHAPE();

        void GL_drawShape(GLFWwindow*window);
		std::string GL_getName();
		GLenum GL_getMemoryLocation();
		GLuint GL_getVAO();
		GLuint GL_getVBO();
		GLuint GL_getShader();
        GLfloat*GL_getVertices()const;
    };
}
