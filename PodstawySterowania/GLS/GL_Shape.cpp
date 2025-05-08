#include "GL_Shape.h"

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
void GLS::GL_VertexData::getVertexData(GLfloat*vertexData)const{
	GLuint i=0;
	for(;i<3;i++)
		vertexData[i]=_xyz[i];
	for(i=0;i<4;i++)
		vertexData[i+3]=_rgba[i];
	for(i=0;i<2;i++)
		vertexData[i+7]=_xyz[i];
}
glm::vec3 GLS::GL_VertexData::getXYZ()const{
	return _xyz;
}
glm::vec4 GLS::GL_VertexData::getRGBA()const{
	return _rgba;
}
glm::vec2 GLS::GL_VertexData::getUV()const{
	return _uv;
}
void GLS::GL_VertexData::setVertexData(glm::vec3 xyz,glm::vec4 rgba,glm::vec2 uv){
	_xyz=xyz;
	_rgba=_rgba;
	_uv=uv;
}
void GLS::GL_VertexData::setVertexData(GLfloat*vertexData){
	this->operator=(vertexData);
}
void GLS::GL_VertexData::setXYZ(glm::vec3 xyz){
	_xyz=xyz;
}
void GLS::GL_VertexData::setRGBA(glm::vec4 rgba){
	_rgba=rgba;
}
void GLS::GL_VertexData::setUV(glm::vec2 uv){
	_uv=uv;
}
GLS::GL_VertexData&GLS::GL_VertexData::operator=(const GLS::GL_VertexData&vertexData){
	_xyz=vertexData.getXYZ();
	_rgba=vertexData.getRGBA();
	_uv=vertexData.getUV();
	return *this;
}
GLS::GL_VertexData&GLS::GL_VertexData::operator+(const GLS::GL_VertexData&vertexData){
    return *this;
}
/////////////////////////////////////////////////////////////
GLS::GL_Shape::GL_Shape(GLuint shaderProgram,GLenum memoryLocation){
	_shaderProgram=shaderProgram;
    _VAO=_VBO=0;
	_memoryLocation=memoryLocation;
	_vertN=0;
}
GLS::GL_Shape::~GL_Shape(){
	glDeleteVertexArrays(1,&_VAO);
	glDeleteBuffers(1,&_VBO);
}
void GLS::GL_Shape::transform(glm::vec3 transformVector){
	glm::mat4 model=glm::mat4(1.0f);
	model=glm::translate(model,glm::vec3(transformVector.x,transformVector.y,transformVector.z));
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
}
void GLS::GL_Shape::rotate(glm::vec3 rotationVector){
	glm::mat4 model=glm::mat4(1.0f);
	model=glm::rotate(model,glm::degrees(rotationVector.z),glm::vec3(0,0,1));
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
}
GLenum GLS::GL_Shape::getMemoryLocation()const{
	return _memoryLocation;
}
GLuint GLS::GL_Shape::getVAO()const{
	return _VAO;
}
GLuint GLS::GL_Shape::getVBO()const{
	return _VBO;
}
GLuint GLS::GL_Shape::getShader()const{
	return _shaderProgram;
}
GLS::GL_VertexData GLS::GL_Shape::getVertices()const{
	return *_vertices;
}
/////////////////////////////////////////////////////////////
GLS::GL_Triangle::GL_Triangle(GLS::GL_VertexData*vertices,GLuint shaderProgram,GLenum memoryLocation):GL_Shape(shaderProgram,memoryLocation){
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
GLS::GL_Triangle::GL_Triangle(GLuint shaderProgram,GLenum memoryLocation):GL_Shape(shaderProgram,memoryLocation){
	_vertN=3;
	_vertices=new GL_VertexData[_vertN]{};
	GLfloat*test=new GLfloat[GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN]{};

	GLfloat angle=0.0f;
	GLfloat angleIncrement=360.0f/_vertN;
	GLfloat radius=1.0f;
	glm::vec3 xyz{};

	for(GLuint i=0;i<_vertN;i++){
		xyz[0]=std::sin(angle*M_PI/180.0f)*radius;
		xyz[1]=std::cos(angle*M_PI/180.0f)*radius;
		_vertices[i].setXYZ(xyz);
		angle+=angleIncrement;
	}
	for(GLuint i=0;i<_vertN;i++)
		_vertices[i].getVertexData(test+i*GLS::GL_VertexData::GL_VERTEX_SIZE);

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
GLS::GL_Triangle::~GL_Triangle(){
	delete[]_vertices;
}
/////////////////////////////////////////////////////////////
GLS::GL_Polygon::GL_Polygon(GLuint vertN,GLuint shaderProgram,GLenum memoryLocation):GL_Shape(shaderProgram,memoryLocation){
	_vertN=vertN;
	_vertices=new GL_VertexData[_vertN]{};
	_indicesN=(_vertN-2)*3;
	_indices=new GLuint[_indicesN]{};

	for(GLuint i=0,j=1;i<_indicesN;i++){
		if((i%3)==1){
			_indices[i]=j;
			j++;
		}
		if((i%3)==2)
			_indices[i]=j;
	}

	GLfloat*test=new GLfloat[GLS::GL_VertexData::GL_VERTEX_SIZE*_vertN]{};

	GLfloat angle=45.0f;
	GLfloat angleIncrement=360.0f/_vertN;
	GLfloat radius=std::sqrt(2)/2;
	glm::vec3 xyz{};

	for(GLuint i=0;i<_vertN;i++){
		xyz[0]=std::sin(angle*M_PI/180.0f)*radius;
		xyz[1]=std::cos(angle*M_PI/180.0f)*radius;
		_vertices[i].setXYZ(xyz);
		angle+=angleIncrement;
	}
	for(GLuint i=0;i<_vertN;i++)
		_vertices[i].getVertexData(test+i*GLS::GL_VertexData::GL_VERTEX_SIZE);

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
GLS::GL_Polygon::~GL_Polygon(){
	delete[]_indices;
}
GLuint GLS::GL_Polygon::getEBO()const{
	return _EBO;
}
GLuint GLS::GL_Polygon::getIndicesN()const{
	return _indicesN;
}
