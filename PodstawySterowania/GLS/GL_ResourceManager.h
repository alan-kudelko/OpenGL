/*
 * Author: Alan Kude³ko
 * Date: May 2025
 * GitHub: https://github.com/alan-kudelko
 * License: MIT
 *
 * Class GL_ResourceManager & Structs GL_ShapeEntry, GL_ShaderEntry
 * -----------------------------------------------------------------
 * Centralized manager for geometric and shader resources used in rendering.
 * Prevents redundant creation of reusable shapes and shaders by maintaining
 * internal registries with fast lookup based on name or configuration.
 *
 * - GL_ShapeEntry: Stores a pointer to a GL_Shape instance and its vertex count.
 *   Used internally for matching or retrieving shared mesh data.
 *
 * - GL_ShaderEntry: Stores a pointer to a compiled shader program and metadata
 *   such as name and original source file paths. Allows for organized shader reuse.
 *
 * - GL_ResourceManager: 
 *   - Provides access to predefined shapes (e.g., "triangle", "quad") or shapes
 *     matching a specific vertex count
 *   - Caches and returns existing GL_Shape and GL_Shader objects
 *   - Supports dynamic shader creation from source files
 *
 * Intended to improve runtime performance, memory efficiency, and modularity
 * by decoupling geometry and shader creation from individual mesh or object logic.
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
