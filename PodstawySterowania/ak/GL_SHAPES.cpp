#include "GL_SHAPES.h"

ak::GL_SHAPE::GL_SHAPE(GLfloat*vertices,int vertN,std::string name,int shaderProgram,int VAO,int VBO,GLenum memoryLocation){
	_name=name;
	_shaderProgram=shaderProgram;
	_VAO=VAO;
	_VBO=VBO;
	_memoryLocation=memoryLocation;
	_vertN=vertN;
    _vertices=new float[vertN*3];
	for(int i=0;i<vertN*3;i++)
		_vertices[i]=vertices[i];

	glGenVertexArrays(1,&_VAO);
	glGenBuffers(1,&_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,3*_vertN*sizeof(float),_vertices,_memoryLocation);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,_vertN*sizeof(float),(void*)nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
ak::GL_SHAPE::~GL_SHAPE(){
	delete[]_vertices;
	glDeleteVertexArrays(1,&_VAO);
	glDeleteBuffers(1,&_VBO);
}
void ak::GL_SHAPE::GL_drawShape(GLFWwindow*window){
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES,0,3);
}
std::string ak::GL_SHAPE::GL_getName(){
	return _name;
}
GLenum ak::GL_getMemoryLocation(){
	return _memoryLocation;
}
GLuint ak::GL_getVAO(){
	return _VAO;
}
GLuint ak::GL_getVBO(){
	return _VBO;
}
GLuint ak::GL_getShader(){
	return _shaderProgram;
}
