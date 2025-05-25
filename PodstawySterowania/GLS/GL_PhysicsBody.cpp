#include "GL_PhysicsBody.h"

GLS::GL_PhysicsBody::GL_PhysicsBody(){
	_physicsActive=GL_FALSE;
	_gravityActive=GL_FALSE;
	
	_mass=1.0f;
	
	_linearVelocity=glm::vec3(0.0f);
	_angularVelocity=glm::vec3(0.0f);
	
	_linearAcceleration=glm::vec3(0.0f);
	_angularAcceleration=glm::vec3(0.0f);
	
	_centerOffMass=glm::vec3(0.0f);
}
GLS::GL_PhysicsBody::~GL_PhysicsBody(){
	
}
////////////////////////////////////////////////////////////////// Physics enable operations
GLboolean GLS::GL_PhysicsBody::isPhysicsActive()const{
	return _physicsActive;
}
void GLS::GL_PhysicsBody::enablePhysics(){
	_physicsActive=GL_TRUE;
}
void GLS::GL_PhysicsBody::disablePhysics(){
	_physicsActive=GL_FALSE;
}
////////////////////////////////////////////////////////////////// Gravity operations
GLboolean GLS::GL_PhysicsBody::isGravityActive()const{
	return _physicsActive;
}
void GLS::GL_PhysicsBody::enableGravity(){
	_gravityActive=GL_TRUE;
}
void GLS::GL_PhysicsBody::disableGravity(){
	_gravityActive=GL_FALSE;	
}
////////////////////////////////////////////////////////////////// Mass operations
GLfloat GLS::GL_PhysicsBody::getMass()const{
	return _mass;
}
void GLS::GL_PhysicsBody::setMass(GLfloat mass){
	_mass=mass;
}
////////////////////////////////////////////////////////////////// Linear velocity operations
glm::vec2 GLS::GL_PhysicsBody::getLinearVelocity()const{
	return _linearVelocity;
}
void GLS::GL_PhysicsBody::setLinearVelocity(glm::vec2 linearVelocity){
	_linearVelocity=linearVelocity;
}
////////////////////////////////////////////////////////////////// Angular velocity operations
glm::vec3 GLS::GL_PhysicsBody::getAngularVelocity()const{
	return _angularVelocity;
}
void GLS::GL_PhysicsBody::setAngularVelocity(glm::vec3 angularVelocity){
	_angularVelocity=angularVelocity;
}
////////////////////////////////////////////////////////////////// Linear acceleration operations
glm::vec2 GLS::GL_PhysicsBody::getLinearAcceleration()const{
	return _linearAcceleration;
}
void GLS::GL_PhysicsBody::setLinearAcceleration(glm::vec2 linearAcceleration){
	_linearAcceleration=linearAcceleration;
}
////////////////////////////////////////////////////////////////// Angular acceleration operations
glm::vec3 GLS::GL_PhysicsBody::getAngularAcceleration()const{
	return _angularAcceleration;
}
void GLS::GL_PhysicsBody::setAngularAcceleration(glm::vec3 angularAcceleration){
	_angularAcceleration=angularAcceleration;
}
