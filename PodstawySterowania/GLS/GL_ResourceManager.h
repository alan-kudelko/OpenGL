/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_GeometryManager & Struct GL_ShapeEntry
 * -----------------------------------------------
 * Centralized manager for geometric shape instances used in rendering.
 *
 * GL_ShapeEntry: Struct storing a pointer to a shape (GL_Shape)
 *   and its corresponding vertex count. Used internally to track reusable shapes.
 *
 * GL_ResourceManager: Provides mechanisms to retrieve or reuse predefined geometry
 *   either by name (e.g., "triangle", "quad") or by raw vertex count.
 *   Internally maintains a record of created shapes for efficient lookup.
 *
 * Intended to support geometry sharing and caching across multiple mesh instances,
 * reducing redundant shape creation and improving performance.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLS{
    class GL_Shape;
	class GL_Shader;
	// Class GL_Texture in the future

    struct GL_ShapeEntry{ // Struct for storing pointer to created geometry and its vertex count
        GLS::GL_Shape*shape;
        GLuint vertN;
    };
	struct GL_ShaderEntry{ // Struct for storing pointer 
		GLS::GL_Shader*shader;
		std::string shaderName;
		std::string vertexShaderPath;
		std::string fragmentShaderPath;
	};
	class GL_ResourceManager{
		std::vector<GLS::GL_ShapeEntry>_shapeRecords;
		std::vector<GLS::GL_ShaderEntry>_shaderRecords;
		
		auto _findGeometryByVertCount(GLuint vertN)const;
		auto _findShaderByName(std::string shaderName)const;
	public:
		GL_ResourceManager();
		~GL_ResourceManager();
		
		GLS::GL_Shape*getGeometryByName(std::string meshType); // Returns GL_Shape by its predifined name
		GLS::GL_Shape*getGeometryByVertCount(GLuint vertN); // Returns GL_Shape by its predifined vertex count
		
		void createShader(std::string shaderName,std::string vertexShaderPath,std::string fragmentShaderPath);
		
		GLS::GL_Shader*getShaderByName(std::string shaderName)const; // Returns GL_Shader by its name
		
	};
}
