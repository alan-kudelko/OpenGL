#include "GL_CollisionManager.h"


GLS::GL_CollisionManager::GL_CollisionManager(){

}
GLS::GL_CollisionManager::~GL_CollisionManager(){

}
GLboolean GLS::GL_CollisionManager::checkCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2){
	// Checking if these two objects have GL_Collider component
	// Checking if two objects are in the same collisionGroup
	// AABB testing
	const GLS::GL_Collider*obj1Collider=obj1->getColliderComponent();
	const GLS::GL_Collider*obj2Collider=obj2->getColliderComponent();

	if(obj1Collider==nullptr)
		return GL_FALSE;
	if(obj2Collider==nullptr)
		return GL_FALSE;
	if(obj1Collider->getCollisionGroup()!=obj2Collider->getCollisionGroup())
		return false;


}
