#pragma once
#include <string>
#include <glad.h>
#include <glfw3.h>

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