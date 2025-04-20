#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace GLS{
	class GPUResourceTracker{
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
        GPUResourceTracker();
        ~GPUResourceTracker();
        GLuint getFirstEmptyVAO()const;
        GLuint getFirstEmptyVBO()const;
		GLuint getFirstEBO()const;
        GLuint getFirstEmptyShader()const;

        GLuint addFirstEmptyVAO();
        GLuint addFirstEmptyVBO();
	    GLuint addFirstEmptyEBO();
        GLuint addFirstEmptyShader();

        GLuint getNumberVAO()const;
        GLuint getNumberVBO()const;
        GLuint getNumberEBO()const;		
        GLuint getNumberShader()const;
		
		GLuint removeVAO(GLuint _VAO);
		GLuint removeVBO(GLuint _VBO);
		GLuint removeEBO(GLuint _EBO);
		GLuint removeShader(GLuint _Shader);
	};
}
