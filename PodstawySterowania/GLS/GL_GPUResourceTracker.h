#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace GLS{
	class GL_GPUResourceTracker{
		GLboolean*_VAO_List;
		GLboolean*_VBO_List;
		GLboolean*_EBO_List;
		GLboolean*_Shader_List;

		GLuint _VAO_N;
		GLuint _VBO_N;
		GLuint _EBO_N;
		GLuint _Shader_N;

		GLuint _VAO_N_Capacity;
		GLuint _VBO_N_Capacity;
		GLuint _EBO_N_Capacity;
		GLuint _Shader_N_Capacity;
    public:
        GL_GPUResourceTracker();
        ~GL_GPUResourceTracker();
        GLuint getFirstEmptyVAO()const;
        GLuint getFirstEmptyVBO()const;
		GLuint getFirstEmptyEBO()const;
        GLuint getFirstEmptyShader()const;

        GLuint addVAO();
        GLuint addVBO();
	    GLuint addEBO();
        GLuint addShader();

        GLuint getNumberVAO()const;
        GLuint getNumberVBO()const;
        GLuint getNumberEBO()const;
        GLuint getNumberShader()const;

		GLuint removeVAO(GLuint VAO);
		GLuint removeVBO(GLuint VBO);
		GLuint removeEBO(GLuint EBO);
		GLuint removeShader(GLuint Shader);
	};
}
