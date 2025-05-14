#include "GL_CollisionBehaviour.h"
#include "GL_GameObject.h"

void GLS::behaviourDestroyAfterCollision(GLS::GL_GameObject*gameObject){
	gameObject->markForDestruction();
}
void GLS::behaviourReverseVelocityAfterCollision(GLS::GL_GameObject*gameObject){
	glm::vec3 velocity=gameObject->getGameObjectLinearVelocity();
	
	gameObject->setGameObjectLinearVelocity(-velocity);
}
void GLS::behaviourDoNothing(GLS::GL_GameObject*gameObject){
	
}
GLS::GL_CollisionBehaviour::GL_CollisionBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*)){
	_behaviourActive=GL_TRUE;
	_behaviourFunPtr=behaviourFunPtr;
}
GLS::GL_CollisionBehaviour::~GL_CollisionBehaviour(){

}
void GLS::GL_CollisionBehaviour::addBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*)){
	_behaviourFunPtr=behaviourFunPtr;
}
void GLS::GL_CollisionBehaviour::callBehaviour(GLS::GL_GameObject*gameObject){
	if(_behaviourActive==GL_TRUE)
		_behaviourFunPtr(gameObject);
}
void GLS::GL_CollisionBehaviour::enableBehaviour(){
	_behaviourActive=GL_TRUE;
}
void GLS::GL_CollisionBehaviour::disableBehaviour(){
	_behaviourActive=GL_FALSE;
}
GLboolean GLS::GL_CollisionBehaviour::behaviourActive()const{
	return _behaviourActive;
}
