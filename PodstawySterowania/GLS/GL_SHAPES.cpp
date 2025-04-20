#include "GL_SHAPES.h"

GLS::GL_SHAPE::GL_SHAPE(GLfloat*vertices,GLuint vertN,std::string name,GLuint shaderProgram,GLuint VAO,GLuint VBO,GLenum memoryLocation){
	_name=name;
	_shaderProgram=shaderProgram;
	_VAO=VAO;
	_VBO=VBO;
	_memoryLocation=memoryLocation;
	_vertN=vertN;

	if(vertN>0)
		_vertices=new GLfloat[vertN*3];
	for(GLuint i=0;i<vertN*3;i++)
		_vertices[i]=vertices[i];
}
GLS::GL_SHAPE::~GL_SHAPE(){
	delete[]_vertices;
	glDeleteVertexArrays(1,&_VAO);
	glDeleteBuffers(1,&_VBO);
}
std::string GLS::GL_SHAPE::GL_getName()const{
	return _name;
}
GLenum GLS::GL_SHAPE::GL_getMemoryLocation()const{
	return _memoryLocation;
}
GLuint GLS::GL_SHAPE::GL_getVAO()const{
	return _VAO;
}
GLuint GLS::GL_SHAPE::GL_getVBO()const{
	return _VBO;
}
GLuint GLS::GL_SHAPE::GL_getShader()const{
	return _shaderProgram;
}
/////////////////////////////////////////////////////////////
GLS::GL_TRIANGLE::GL_TRIANGLE(GLfloat*vertices,GLuint vertN,std::string name,GLuint shaderProgram,GLuint VAO,GLuint VBO,GLenum memoryLocation):GL_SHAPE(vertices,vertN,name,shaderProgram,VAO,VBO,memoryLocation){
	glGenVertexArrays(1,&_VAO);
	glGenBuffers(1,&_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,3*_vertN*sizeof(GLfloat),_vertices,_memoryLocation);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,_vertN*sizeof(GLfloat),(void*)nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
GLS::GL_TRIANGLE::~GL_TRIANGLE(){

}
void GLS::GL_TRIANGLE::GL_drawShape(GLFWwindow*window){
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES,0,3);
}
/////////////////////////////////////////////////////////////
GLS::GL_RECTANGLE::GL_RECTANGLE(GLfloat*vertices,GLuint vertN,std::string name,GLuint shaderProgram,GLuint VAO,GLuint VBO,GLenum memoryLocation):GL_SHAPE(vertices,vertN,name,shaderProgram,VAO,VBO,memoryLocation){
	_EBO=1;
	glGenVertexArrays(1,&_VAO);
	glGenBuffers(1,&_VBO);
	glGenBuffers(1,&_EBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,3*_vertN*sizeof(GLfloat),_vertices,_memoryLocation);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(_indices),_indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)nullptr);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
GLS::GL_RECTANGLE::~GL_RECTANGLE(){
}
void GLS::GL_RECTANGLE::GL_drawShape(GLFWwindow*window){
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	//glDrawArrays(GL_TRIANGLES,0,3);
}
