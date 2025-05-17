#include "GL_CollisionBehaviour.h"
#include "GL_GameObject.h"

void GLS::behaviourDestroyAfterCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2){
	obj1->markForDestruction();
}
void GLS::behaviourReverseVelocityAfterCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2){
	glm::vec3 obj1LinearVelocity=obj1->getGameObjectLinearVelocity();
	glm::vec3 obj1NormalizedVelocityVector=obj1LinearVelocity/obj1LinearVelocity;
	
	// I think i need to know which direction is outside of GL_Collider
	
	glm::vec3 velocity=obj1->getGameObjectLinearVelocity();

	obj1->setGameObjectLinearVelocity(-velocity);
}
void GLS::behaviourDoNothing(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2){

}
GLS::GL_CollisionBehaviour::GL_CollisionBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)){
	_behaviourActive=GL_TRUE;
	_behaviourFunPtr=behaviourFunPtr;
}
GLS::GL_CollisionBehaviour::~GL_CollisionBehaviour(){

}
void GLS::GL_CollisionBehaviour::addBehaviour(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)){
	_behaviourFunPtr=behaviourFunPtr;
}
void GLS::GL_CollisionBehaviour::callBehaviour(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2){
	if(_behaviourActive==GL_TRUE)
		_behaviourFunPtr(obj1,obj2);
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
