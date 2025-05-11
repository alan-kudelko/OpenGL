#include "GL_Collider.h"


GLS::GL_Collider::GL_Collider(glm::vec3 boundingBoxLocation,glm::vec3 boundingBoxSize,GLuint collisionGroup){
	_boundingBoxLocation=boundingBoxLocation;
	_originalBoundingBoxSize=boundingBoxSize;
	_collisionGroup=collisionGroup;
	_transformedBoundingBoxSize=boundingBoxSize;
}
GLS::GL_Collider::~GL_Collider(){

}
GLuint GLS::GL_Collider::getCollisionGroup()const{
	return _collisionGroup;
}
glm::vec3 GLS::GL_Collider::getBoundingBoxLocation()const{
	return _boundingBoxLocation;
}
glm::vec3 GLS::GL_Collider::getBoundingBoxSize()const{
	return _originalBoundingBoxSize;
}
glm::vec3 GLS::GL_Collider::getBoundingBoxMin()const{
	return _boundingBoxLocation-_transformedBoundingBoxSize/2.0f;
}
glm::vec3 GLS::GL_Collider::getBoundingBoxMax()const{
	return _boundingBoxLocation+_transformedBoundingBoxSize/2.0f;
}
void GLS::GL_Collider::setCollisionGroup(GLuint collisionGroup){
	_collisionGroup=collisionGroup;
}
void GLS::GL_Collider::setBoundingBoxLocation(glm::vec3 boundingBoxLocation){
	_boundingBoxLocation=boundingBoxLocation;
}
void GLS::GL_Collider::setBoundingBoxSize(glm::vec3 boudingBoxSize){
	_originalBoundingBoxSize=boudingBoxSize;
}
void GLS::GL_Collider::updateBoundingBoxSize(glm::vec3 rotation){
	glm::mat3 boundingBoxRotation=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(rotation.z),glm::vec3(0.0f,0.0f,1.0f)));
	
	auto mat3abs=[](glm::mat3&m){
		for(GLuint i=0;i<3;i++)
			m[i]=glm::abs(m[i]);
        return m;
	};	
	
	_transformedBoundingBoxSize=mat3abs(boundingBoxRotation)*_originalBoundingBoxSize;
}