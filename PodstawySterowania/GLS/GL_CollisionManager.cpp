#include "GL_CollisionManager.h"
#include "GL_Collider.h"

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
		return GL_FALSE;
	if(!(obj1Collider->shouldCollide())&&(obj2Collider->shouldCollide()))
		return GL_FALSE;

	glm::vec3 obj1GameObjectPosition=obj1->getGameObjectLocation();
	glm::vec3 obj2GameObjectPosition=obj2->getGameObjectLocation();

	glm::vec3 obj1GameObjectRotation=obj1->getGameObjectRotation();
	glm::vec3 obj2GameObjectRotation=obj2->getGameObjectRotation();

	// This will be changed as the colllider is changed

	glm::vec3 obj1BoundingBoxMin=obj1Collider->getBoundingBoxMin()+obj1GameObjectPosition;
	glm::vec3 obj1BoundingBoxMax=obj1Collider->getBoundingBoxMax()+obj1GameObjectPosition;
	glm::vec3 obj2BoundingBoxMin=obj2Collider->getBoundingBoxMin()+obj2GameObjectPosition;
	glm::vec3 obj2BoundingBoxMax=obj2Collider->getBoundingBoxMax()+obj2GameObjectPosition;

	GLboolean didCollide=GL_FALSE;
	// AABB
	if((obj1BoundingBoxMax.x>obj2BoundingBoxMin.x&&obj1BoundingBoxMin.x<obj2BoundingBoxMax.x)&&
           (obj1BoundingBoxMax.y>obj2BoundingBoxMin.y&&obj1BoundingBoxMin.y<obj2BoundingBoxMax.y)&&
           (obj1BoundingBoxMax.z>obj2BoundingBoxMin.z&&obj1BoundingBoxMin.z<obj2BoundingBoxMax.z)){
		(obj1->getCollisionBehaviourComponent())->callBehaviour(obj1);
		(obj2->getCollisionBehaviourComponent())->callBehaviour(obj2);
		std::cout<<"Kolizja"<<std::endl;
		didCollide=GL_TRUE;
	}

	return didCollide;
}
