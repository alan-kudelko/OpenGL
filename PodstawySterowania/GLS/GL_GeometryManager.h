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

    struct GL_ShapeEntry{ // Struct for storing pointer to created geometry and its vertex count
        GLS::GL_Shape*shape;
        GLuint vertN;
    };
	class GL_GeometryManager{
		std::vector<GLS::GL_ShapeEntry>_shapeRecords;
		auto _findGeometryByVertCount(GLuint vertN)const;
	public:
		GL_GeometryManager();
		~GL_GeometryManager();

		GLS::GL_Shape*getGeometryByName(std::string meshType); // Returns GL_Shape by its predifined name
		GLS::GL_Shape*getGeometryByVertCount(GLuint vertN); // Returns GL_Shape by its predifined vertex count
	};
}
