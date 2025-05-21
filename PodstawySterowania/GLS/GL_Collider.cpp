#include "GL_Collider.h"
#include "GL_Transform.h"

////////////////////////////////////////////////////////////////// GL_Collider
GLS::GL_Collider::GL_Collider(glm::vec3 location,glm::vec3 rotation,glm::vec3 scale,GLuint collisionGroup){
	_localTransform.setLocation(location);
	_localTransform.setRotation(rotation);
	_localTransform.setScale(scale);
	_transformedScale=scale;
	_collisionGroup=collisionGroup;
	_collisionEnable=GL_TRUE;
}
GLS::GL_Collider::~GL_Collider(){

}
GLuint GLS::GL_Collider::getCollisionGroup()const{
	return _collisionGroup;
}
glm::vec3 GLS::GL_Collider::getLocalLocation()const{
	return _localTransform.getLocation();
}
glm::vec3 GLS::GL_Collider::getLocalRotation()const{
	return _localTransform.getRotation();
}
glm::vec3 GLS::GL_Collider::getLocalScale()const{
	return _localTransform.getScale();
}
glm::vec3 GLS::GL_Collider::getBoundingBoxMin()const{
	return _localTransform.getLocation()-_transformedScale/2.0f;
}
glm::vec3 GLS::GL_Collider::getBoundingBoxMax()const{
	return _localTransform.getLocation()+_transformedScale/2.0f;
}
void GLS::GL_Collider::setCollisionGroup(GLuint collisionGroup){
	_collisionGroup=collisionGroup;
}
void GLS::GL_Collider::setLocalLocation(glm::vec3 location){
	_localTransform.setLocation(location);
}
void GLS::GL_Collider::setLocalRotation(glm::vec3 rotation){
	_localTransform.setRotation(rotation);
}
void GLS::GL_Collider::setLocalScale(glm::vec3 scale){
	_localTransform.setScale(scale);
}
void GLS::GL_Collider::updateBoundingBoxSize(glm::vec3 rotation){
	glm::mat3 boundingBoxRotation=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(rotation.z),glm::vec3(0.0f,0.0f,1.0f)));

	auto mat3abs=[](glm::mat3&m){
		for(GLuint i=0;i<3;i++)
			m[i]=glm::abs(m[i]);
        return m;
	};

	_transformedScale=mat3abs(boundingBoxRotation)*_localTransform.getScale();
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
////////////////////////////////////////////////////////////////// GL_SphereCollider
GLS::GL_SphereCollider::GL_SphereCollider(glm::vec3 location,glm::vec3 rotation,glm::vec3 scale,GLuint collisionGroup):GL_Collider(location,rotation,scale,collisionGroup){
	
}
GLS::GL_SphereCollider::~GL_SphereCollider(){

}