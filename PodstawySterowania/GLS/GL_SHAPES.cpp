#include "GL_SHAPES.h"

GLS::GL_GPUResourceTracker GL_GPUresourceTracker;

GLS::GL_VertexData::GL_VertexData(GLfloat*vertex){
	if(vertex==nullptr)
		return;
	GLuint i=0;
	for(;i<3;i++)
		_xyz[i]=vertex[i];
	for(i=0;i<3;i++)
		_rgba[i]=vertex[i+3];
	for(i=0;i<2;i++)
		_uv[i]=vertex[i+7];
}
GLS::GL_VertexData::GL_VertexData(glm::vec3 xyz,glm::vec4 rgba,glm::vec2 uv){
	_xyz=xyz;
	_rgba=_rgba;
	_uv=uv;
}
void GLS::GL_VertexData::GLgetVertexData(GLfloat*vertexData)const{
	GLuint i=0;
	for(;i<3;i++)
		vertexData[i]=_xyz[i];
	for(i=0;i<4;i++)
		vertexData[i+3]=_rgba[i];
	for(i=0;i<2;i++)
		vertexData[i+7]=_xyz[i];
}
glm::vec3 GLS::GL_VertexData::GLgetXYZ()const{
	return _xyz;
}
glm::vec4 GLS::GL_VertexData::GLgetRGBA()const{
	return _rgba;
}
glm::vec2 GLS::GL_VertexData::GLgetUV()const{
	return _uv;
}
void GLS::GL_VertexData::GLsetVertexData(glm::vec3 xyz,glm::vec4 rgba,glm::vec2 uv){
	_xyz=xyz;
	_rgba=_rgba;
	_uv=uv;
}
void GLS::GL_VertexData::GLsetVertexData(GLfloat*vertexData){
	this->operator=(vertexData);
}
void GLS::GL_VertexData::GLsetXYZ(glm::vec3 xyz){
	_xyz=xyz;
}
void GLS::GL_VertexData::GLsetRGBA(glm::vec4 rgba){
	_rgba=rgba;
}
void GLS::GL_VertexData::GLsetUV(glm::vec2 uv){
	_uv=uv;
}
GLS::GL_VertexData&GLS::GL_VertexData::operator=(const GLS::GL_VertexData&vertexData){
	_xyz=vertexData.GLgetXYZ();
	_rgba=vertexData.GLgetRGBA();
	_uv=vertexData.GLgetUV();
	return *this;
}
GLS::GL_VertexData&GLS::GL_VertexData::operator+(const GLS::GL_VertexData&vertexData){
    return *this;
}
/////////////////////////////////////////////////////////////
GLS::GL_SHAPE::GL_SHAPE(GLuint shaderProgram,GLenum memoryLocation){
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
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
}
void GLS::GL_SHAPE::GLrotate(glm::vec3 rotationVector){
	glm::mat4 model=glm::mat4(1.0f);
	model=glm::rotate(model,glm::degrees(rotationVector.z),glm::vec3(0,0,1));
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
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
GLS::GL_VertexData GLS::GL_SHAPE::GLgetVertices()const{
	return *_vertices;
}
/////////////////////////////////////////////////////////////
GLS::GL_TRIANGLE::GL_TRIANGLE(GLS::GL_VertexData*vertices,GLuint shaderProgram,GLenum memoryLocation):GL_SHAPE(shaderProgram,memoryLocation){
	_vertN=3;
	_vertices=new GL_VertexData[3]{};

	for(GLuint i=0;i<_vertN;i++)
		_vertices[i]=vertices[i];

	glGenVertexArrays(1,&_VAO);
	glGenBuffers(1,&_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN*sizeof(GLfloat),_vertices,_memoryLocation);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)0);
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)(7*sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
GLS::GL_TRIANGLE::GL_TRIANGLE(GLuint shaderProgram,GLenum memoryLocation):GL_SHAPE(shaderProgram,memoryLocation){
	_vertN=3;
	_vertices=new GL_VertexData[_vertN]{};
	GLfloat*test=new GLfloat[GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN]{};

	GLfloat angle=0.0f;
	GLfloat angleIncrement=360.0f/_vertN;
	GLfloat radius=0.5f;
	glm::vec3 xyz{};

	for(GLuint i=0;i<_vertN;i++){
		xyz[0]=std::sin(angle*M_PI/180.0f)*radius;
		xyz[1]=std::cos(angle*M_PI/180.0f)*radius;
		_vertices[i].GLsetXYZ(xyz);
		angle+=angleIncrement;
	}
	for(GLuint i=0;i<_vertN;i++)
		_vertices[i].GLgetVertexData(test+i*GLS::GL_VertexData::GL_VERTEX_SIZE);

	glGenVertexArrays(1,&_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1,&_VBO);
	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN*sizeof(GLfloat),test,_memoryLocation);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)0);
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)(7*sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	delete[]test;
}
GLS::GL_TRIANGLE::~GL_TRIANGLE(){
	delete[]_vertices;
}
void GLS::GL_TRIANGLE::GLdrawShape()const{
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES,0,3);
}
/////////////////////////////////////////////////////////////
GLS::GL_POLYGON::GL_POLYGON(GLuint vertN,GLuint shaderProgram,GLenum memoryLocation):GL_SHAPE(shaderProgram,memoryLocation){
	_vertN=vertN;
	_vertices=new GL_VertexData[_vertN]{};
	_indicesN=(_vertN-2)*3;
	_indices=new GLuint[_indicesN]{0,1,3,1,2,3};
	GLfloat*test=new GLfloat[GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN]{};

	_EBO=GL_GPUresourceTracker.addEBO();

	GLfloat angle=0.0f;
	GLfloat angleIncrement=360.0f/_vertN;
	GLfloat radius=0.5f;
	glm::vec3 xyz{};

	for(GLuint i=0;i<_vertN;i++){
		xyz[0]=std::sin(angle*M_PI/180.0f)*radius;
		xyz[1]=std::cos(angle*M_PI/180.0f)*radius;	
		_vertices[i].GLsetXYZ(xyz);
		angle+=angleIncrement;
	}
	for(GLuint i=0;i<_vertN;i++)
		_vertices[i].GLgetVertexData(test+i*GLS::GL_VertexData::GL_VERTEX_SIZE);
	
	glGenVertexArrays(1,&_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1,&_VBO);
	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN*sizeof(GLfloat),test,_memoryLocation);
	
	glGenBuffers(1,&_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*_indicesN,_indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)0);
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,GLS::GL_VertexData::GL_VERTEX_SIZE*sizeof(GLfloat),(void*)(7*sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	delete[]test;
}
GLS::GL_POLYGON::~GL_POLYGON(){
	delete[]_indices;
}
void GLS::GL_POLYGON::GLdrawShape()const{
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}
