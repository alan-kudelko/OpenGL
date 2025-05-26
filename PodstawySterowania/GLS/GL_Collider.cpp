#include "GL_Collider.h"
#include "GL_Transform.h"

////////////////////////////////////////////////////////////////// GL_Collider
GLS::GL_Collider::GL_Collider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup){
	_localTransform.setLocation(location);
	_localTransform.setRotation(rotation);
	_localTransform.setScale(scale);
	_collisionGroup=collisionGroup;
	_collisionEnable=GL_TRUE;
}
GLS::GL_Collider::~GL_Collider(){

}
GLuint GLS::GL_Collider::getCollisionGroup()const{
	return _collisionGroup;
}
GLS::GL_Transform GLS::GL_Collider::getLocalTransform()const{
	return _localTransform;
}
glm::vec2 GLS::GL_Collider::getLocalLocation()const{
	return _localTransform.getLocation();
}
glm::vec3 GLS::GL_Collider::getLocalRotation()const{
	return _localTransform.getRotation();
}
glm::vec2 GLS::GL_Collider::getLocalScale()const{
	return _localTransform.getScale();
}
void GLS::GL_Collider::setCollisionGroup(GLuint collisionGroup){
	_collisionGroup=collisionGroup;
}
void GLS::GL_Collider::setLocalLocation(glm::vec2 location){
	_localTransform.setLocation(location);
}
void GLS::GL_Collider::setLocalRotation(glm::vec3 rotation){
	_localTransform.setRotation(rotation);
}
void GLS::GL_Collider::setLocalScale(glm::vec2 scale){
	_localTransform.setScale(scale);
}
void GLS::GL_Collider::enableCollisions(){
	_collisionEnable=GL_TRUE;
}
void GLS::GL_Collider::disableCollisions(){
	_collisionEnable=GL_FALSE;
}
GLboolean GLS::GL_Collider::shouldCollide()const{
	return _collisionEnable;
}
void GLS::GL_Collider::getAABBvertices(glm::vec2* AABB)const{
	for(GLuint i=0;i<4;i++)
		AABB[i]=_AABBvertices[i];
}
void GLS::GL_Collider::setAABBvertices(glm::vec2* AABB){
	for(GLuint i=0;i<4;i++)
		_AABBvertices[i]=AABB[i];
}
void GLS::GL_Collider::setAABBvertices(std::vector<glm::vec2> AABB){
	for(GLuint i=0;i<4;i++)
		_AABBvertices[i]=AABB[i];
}
////////////////////////////////////////////////////////////////// GL_BoxCollider
GLS::GL_BoxCollider::GL_BoxCollider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup):GLS::GL_Collider(location,rotation,scale,collisionGroup){
	_boxVertices=new glm::vec2[4]{};

	GLfloat angle=45.0f;
	GLfloat angleIncrement=90.0f;
	GLfloat radius=sqrt(2)/2;

	for(GLuint i=0;i < 4;i++,angle+=angleIncrement){
		_boxVertices[i].x=std::sin(glm::radians(angle))*radius;
		_boxVertices[i].y=std::cos(glm::radians(angle))*radius;
	}
}
GLS::GL_BoxCollider::~GL_BoxCollider(){
	delete[]_boxVertices;
}
void GLS::GL_BoxCollider::getBoxVertices(glm::vec2*vertices)const{
	for (GLuint i=0;i<4;i++) {
		vertices[i]=_boxVertices[i];
	}
}
////////////////////////////////////////////////////////////////// GL_MeshCollider
GLS::GL_MeshCollider::GL_MeshCollider(){

	_isConvex=GL_TRUE;
}
GLS::GL_MeshCollider::~GL_MeshCollider(){

}
////////////////////////////////////////////////////////////////// GL_SphereCollider
GLS::GL_SphereCollider::GL_SphereCollider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup):GL_Collider(location,rotation,scale,collisionGroup){
	
}
GLS::GL_SphereCollider::~GL_SphereCollider(){

}