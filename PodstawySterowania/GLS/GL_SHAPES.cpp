#include "GL_SHAPES.h"

GLS::GL_GPUResourceTracker GL_GPUresourceTracker;

GLS::GL_SHAPE::GL_SHAPE(std::string name,GLuint shaderProgram,GLenum memoryLocation){
	_name=name;
	_shaderProgram=shaderProgram;
    _VAO=GL_GPUresourceTracker.addVAO();
	_VBO=GL_GPUresourceTracker.addVBO();
	_memoryLocation=memoryLocation;
	_vertN=0;
}
GLS::GL_SHAPE::~GL_SHAPE(){
	glDeleteVertexArrays(1,&_VAO);
	glDeleteBuffers(1,&_VBO);

	GL_GPUresourceTracker.removeVAO(_VAO);
	GL_GPUresourceTracker.removeVAO(_VBO);
}
void GLS::GL_SHAPE::GLtransform(glm::vec3 transformVector){
	glm::mat4 model=glm::mat4(1.0f);
	model=glm::translate(model,glm::vec3(transformVector.x,transformVector.y,transformVector.z));
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "model"),1,GL_FALSE,glm::value_ptr(model));
}
void GLS::GL_SHAPE::GLrotate(glm::vec3 rotationVector){
	glm::mat4 model=glm::mat4(1.0f);
	model=glm::rotate(model,glm::degrees(rotationVector.z),glm::vec3(0,0,1));
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
}
std::string GLS::GL_SHAPE::GLgetName()const{
	return _name;
}
GLenum GLS::GL_SHAPE::GLgetMemoryLocation()const{
	return _memoryLocation;
}
GLuint GLS::GL_SHAPE::GLgetVAO()const{
	return _VAO;
}
GLuint GLS::GL_SHAPE::GLgetVBO()const{
	return _VBO;
}
GLuint GLS::GL_SHAPE::GLgetShader()const{
	return _shaderProgram;
}
/////////////////////////////////////////////////////////////
GLS::GL_TRIANGLE::GL_TRIANGLE(GLfloat*vertices,std::string name,GLuint shaderProgram,GLenum memoryLocation):GL_SHAPE(name,shaderProgram,memoryLocation){
	_vertN=3;
	_vertices=new GLfloat[3*3];
	for(GLuint i=0;i<_vertN*3;i++)
		_vertices[i]=vertices[i];

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
	delete[]_vertices;
}
void GLS::GL_TRIANGLE::GLdrawShape(GLFWwindow*window){
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES,0,3);
}
/////////////////////////////////////////////////////////////
GLS::GL_RECTANGLE::GL_RECTANGLE(GLfloat*vertices,std::string name,GLuint shaderProgram,GLenum memoryLocation):GL_SHAPE(name,shaderProgram,memoryLocation){
	_vertN=4;
	_vertices=new GLfloat[4*3];
	for(GLuint i=0;i<_vertN*3;i++)
		_vertices[i]=vertices[i];

	_EBO=GL_GPUresourceTracker.addEBO();
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
void GLS::GL_RECTANGLE::GLdrawShape(GLFWwindow*window){
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}
