#include "GL_CollisionManager.h"
#include "GL_GameObject.h"
#include "GL_Collider.h"
#include "GL_CollisionResolve.h"

GLboolean GLS::GL_CollisionManager::_checkAABBCollision(GLS::GL_GameObject*obj1,GLS::GL_GameObject*obj2){
	const GLS::GL_Collider* obj1Collider=obj1->getColliderComponent();
	const GLS::GL_Collider* obj2Collider=obj2->getColliderComponent();

	glm::vec3 obj1GameObjectPosition=obj1->getLocation();
	glm::vec3 obj2GameObjectPosition=obj2->getLocation();

	glm::vec3 obj1GameObjectRotation=obj1->getRotation();
	glm::vec3 obj2GameObjectRotation=obj2->getRotation();

	glm::vec3 obj1BoundingBoxMin=obj1Collider->getBoundingBoxMin()+obj1GameObjectPosition;
	glm::vec3 obj1BoundingBoxMax=obj1Collider->getBoundingBoxMax()+obj1GameObjectPosition;
	glm::vec3 obj2BoundingBoxMin=obj2Collider->getBoundingBoxMin()+obj2GameObjectPosition;
	glm::vec3 obj2BoundingBoxMax=obj2Collider->getBoundingBoxMax()+obj2GameObjectPosition;
	
	if((obj1BoundingBoxMax.x>obj2BoundingBoxMin.x&&obj1BoundingBoxMin.x<obj2BoundingBoxMax.x)&&
           (obj1BoundingBoxMax.y>obj2BoundingBoxMin.y&&obj1BoundingBoxMin.y<obj2BoundingBoxMax.y)&&
           (obj1BoundingBoxMax.z>obj2BoundingBoxMin.z&&obj1BoundingBoxMin.z<obj2BoundingBoxMax.z)){
		(obj1->getCollisionBehaviourComponent())->callBehaviour(obj1,obj2);
		(obj2->getCollisionBehaviourComponent())->callBehaviour(obj2,obj1);
		return GL_TRUE;
	}
	return GL_FALSE;
}

GLS::GL_CollisionManager::GL_CollisionManager(){

}
GLS::GL_CollisionManager::~GL_CollisionManager(){

}
std::vector<GLS::GL_CollisionInfo>GLS::GL_CollisionManager::checkCollisions(std::vector<GLS::GL_GameObject*>gameObjects){
	// Checking if these two objects have GL_Collider component
	// Checking if two objects are in the same collisionGroup
	const GLS::GL_Collider*obj1Collider=obj1->getColliderComponent();
	const GLS::GL_Collider*obj2Collider=obj2->getColliderComponent();
	std::vector<GLS::GL_CollisionInfo>collisionInfoStruct;

	if(obj1Collider==nullptr)
		return collisionInfoStruct;
	if(obj2Collider==nullptr)
		return collisionInfoStruct;
	if(obj1Collider->getCollisionGroup()!=obj2Collider->getCollisionGroup())
		return collisionInfoStruct;
	if(!(obj1Collider->shouldCollide())&&(obj2Collider->shouldCollide()))
		return collisionInfoStruct;

	glm::vec3 contactPoint;
	glm::vec3 normalVector;
	GLfloat penetrationDepth;

	glm::vec3 obj1GameObjectPosition=obj1->getLocation();
	glm::vec3 obj2GameObjectPosition=obj2->getLocation();

	glm::vec3 obj1GameObjectRotation=obj1->getRotation();
	glm::vec3 obj2GameObjectRotation=obj2->getRotation();

	// AABB
	if(this->_checkAABBCollision(obj1,obj2)){
		std::cout<<"Kolizja AABB"<<std::endl;
		
		GLS::GL_CollisionInfo collisionInfo;
		collisionInfo.obj1=obj1;
		collisionInfo.obj2=obj2;
		collisionInfo.contactPoint=contactPoint;
		collisionInfo.normalVector=normalVector;
		collisionInfo.penetrationDepth=penetrationDepth;
		collisionInfoStruct.push_back(collisionInfo);
	}

	return collisionInfoStruct; // Returns two nullptr if objects did not collide
}
