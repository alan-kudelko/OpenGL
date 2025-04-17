#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum{WINDOW_SIZE_X=600,WINDOW_SIZE_Y=600};
const char*vertexShaderPath="shader/basic_vertex_shader.vert";
const char*fragmentShaderPath="shaders/basic_fragment_shader.frag";

std::string loadShader(const char*path){
    std::stringstream sourceCode;
    std::ifstream file;
    file.open(path,std::ios_base::in);
    sourceCode<<file.rdbuf();
    file.close();
    return sourceCode.str();
}
GLuint compileShader(const char*path,GLenum shaderType){
    std::string shaderCode=loadShader(path);
    const char*sourceCode=shaderCode.c_str();

    GLuint shader=glCreateShader(shaderType);
    glShaderSource(shader,1,&sourceCode,nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
    if(!status){
        char log[512]{};
        glGetShaderInfoLog(shader,512,nullptr,log);
        std::cerr<<log<<std::endl;
        return 0;
    }
    return shader;
}
GLuint createShaderProgram(const char*vertexShaderPath,const char*fragmentShaderPath){
    GLuint vertexShader=compileShader(vertexShaderPath,GL_VERTEX_SHADER);
    GLuint fragmentShader=compileShader(fragmentShaderPath,GL_FRAGMENT_SHADER);

    GLuint shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    int status;
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&status);
    if(!status){
        char infoLog[512]{};
        glGetProgramInfoLog(shaderProgram,512,nullptr,infoLog);
        std::cerr<<infoLog<<std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}



int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow*window=glfwCreateWindow(WINDOW_SIZE_X,WINDOW_SIZE_Y,"Nazwa",NULL,NULL);

    glfwSetWindowAttrib(window,GLFW_RESIZABLE,GLFW_FALSE);

    if(window==nullptr){
        std::cout<<"GLFW failed to create window"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))){
        std::cout<<"GLAD failed to initialize"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);



    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
