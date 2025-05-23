/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Classes: GL_VertexData, GL_Shape, GL_Triangle, GL_Polygon
 * -----------------------------------------------------------
 * Core set of rendering components defining the structure of drawable geometry.
 *
 * - GL_VertexData: Encapsulates vertex attributes such as position, color (RGBA), and UV coordinates.
 *   Designed for flexibility and future extension (e.g., normals, tangents).
 *
 * - GL_Shape: Abstract base class for all geometric primitives. Manages OpenGL buffer objects (VAO, VBO)
 *   and memory allocation modes. Used as a base for shapes rendered in the pipeline.
 *
 * - GL_Triangle: Simple geometric shape consisting of three vertices. Inherits from GL_Shape.
 *
 * - GL_Polygon: More complex shape with optional index buffer (EBO). Supports both indexed and
 *   non-indexed geometry. Designed to handle various primitive types with customizable topology.
 *
 * Intended to serve as a foundation for a modular rendering system,
 * supporting static, dynamic, and streamed geometry in OpenGL.
 */

#pragma once
#define _USE_MATH_DEFINES
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

		enum{GL_VERTEX_SIZE=9}; //Total number of attributes 3+4+2
	};
	// Abstract virtual base class describing shape and all of its parameters
    class GL_Shape:public GL_Component{
	protected:
		GLenum _memoryLocation; // Possible values compliant with OpenGL's memory usage modes: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW
        GLuint _VAO; // Unique handle for the Vertex Array Object (VAO)
        GLuint _VBO; // Unique handle for the Vertex Buffer Object (VBO)
		GL_VertexData*_vertices; // Pointer to primitive's vertices array
		GLuint _vertN; // Number of primitive's vertices
	public:
        GL_Shape(GLenum memoryLocation=GL_DYNAMIC_DRAW);
        virtual ~GL_Shape();

		GLenum getMemoryLocation()const;
		GLuint getVAO()const;
		GLuint getVBO()const;
        GLS::GL_VertexData*getVertices()const;
		GLuint getVertCount()const;
    };
	class GL_Triangle:public GL_Shape{
	public:
		GL_Triangle(GL_VertexData*vertices,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		GL_Triangle(GLenum memoryLocation=GL_DYNAMIC_DRAW);
		~GL_Triangle();
	};
	class GL_Polygon:public GL_Shape{
		GLuint _EBO; // Handle for the EBO
		GLuint*_indices; // Potiner to indices array
		GLuint _indicesN; // Number of elements in the indices array
	public:
		GL_Polygon(GLuint vertN,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		GL_Polygon(GL_VertexData*vertices,GLenum memoryLocation=GL_DYNAMIC_DRAW);
		~GL_Polygon();
		GLuint getEBO()const;
		GLuint getIndicesN()const;
	};
}
