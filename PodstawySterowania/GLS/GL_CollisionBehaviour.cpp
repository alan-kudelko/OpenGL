#include "GL_CollisionBehaviour.h"

void GLS::behaviourDestroyAfterCollision(GLS::GL_GameObject*gameObject){
	gameObject->enableDestruction();
}
GLS::GL_CollisionBehaviour::GL_CollisionBehaviour(){
	_behaviourActive=GL_FALSE;
	_behaviourFunPtr=nullptr;
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
