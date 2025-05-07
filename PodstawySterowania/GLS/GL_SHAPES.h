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
	class GL_VertexData{
		glm::vec3 _xyz; // Vertex's coordinates
		glm::vec4 _rgba; // Vertex's color #RGBA
		glm::vec2 _uv; // Vertex's texture coordinates
		// In the future this class can be extended by adding normals, binormals and other verterx parameters if needed
	public:
		GL_VertexData(GLfloat*vertex);
		GL_VertexData(glm::vec3 xyz={},glm::vec4 rgba={},glm::vec2 uv={});
		void getVertexData(GLfloat*vetexData)const;
		glm::vec3 getXYZ()const;
		glm::vec4 getRGBA()const;
		glm::vec2 getUV()const;
		void setVertexData(glm::vec3 xyz={},glm::vec4 rgba={},glm::vec2 uv={});
		void setVertexData(GLfloat*vertexData);
		void setXYZ(glm::vec3 xyz);
		void setRGBA(glm::vec4 rgba);
		void setUV(glm::vec2 uv);

		GL_VertexData&operator=(const GLS::GL_VertexData&vertexData);
		GL_VertexData&operator+(const GLS::GL_VertexData&vertexData);
		GL_VertexData&operator-(const GLS::GL_VertexData&vertexData);

		enum{GL_VERTEX_SIZE=9}; //Total number of attributes 3+4+2
	};
	// Abstract virtual base class describing shape and all of its parameters
    class GL_SHAPE:public GL_Component{
	protected:
		GLenum _memoryLocation; // Possible values compliant with OpenGL's memory usage modes: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW
        GLuint _VAO; // Unique handle for the Vertex Array Object (VAO)
        GLuint _VBO; // Unique handle for the Vertex Buffer Object (VBO)
		GLuint _shaderProgram; // Handle for the currently bonded shaderProgram
		GL_VertexData*_vertices; // Pointer to primitive's vertices array
		GLuint _vertN; // Number of primitive's vertices
	public:
        GL_SHAPE(GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
        virtual ~GL_SHAPE();

        virtual void drawShape()const=0;
		void transform(glm::vec3 transformVector);
		void rotate(glm::vec3 rotationVector);
		void scale(glm::vec3 scaleVector);
		GLenum getMemoryLocation()const;
		GLuint getVAO()const;
		GLuint getVBO()const;
		GLuint getShader()const;
        GLS::GL_VertexData getVertices()const;
    };
	class GL_TRIANGLE:public GL_SHAPE{
	public:
		GL_TRIANGLE(GL_VertexData*vertices,GLuint shaderProgram,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		GL_TRIANGLE(GLuint shaderProgram,GLenum memoryLocation=GL_STATIC_DRAW);
		~GL_TRIANGLE();
		void drawShape()const override;
	};
	class GL_POLYGON:public GL_SHAPE{
		GLuint _EBO; // Handle for the EBO
		GLuint*_indices; // Potiner to indices array
		GLuint _indicesN; // Number of elements in the indices array
	public:
		GL_POLYGON(GLuint vertN,GLuint shaderProgram=0,GLenum memoryLocation=GL_STATIC_DRAW);
		GL_POLYGON(GL_VertexData*vertices,GLuint shaderProgram,GLenum memoryLocation=GL_STATIC_DRAW);
		~GL_POLYGON();
		void drawShape()const override;
	};
}
/*
	Class for creating and drawing primitives

*/
