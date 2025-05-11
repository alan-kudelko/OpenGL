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

	glm::vec3 obj1GameObjectPosition=obj1->getGameObjectLocation();
	glm::vec3 obj2GameObjectPosition=obj2->getGameObjectLocation();
	glm::vec3 obj1GameObjectRotation=obj1->getGameObjectRotation();
	glm::vec3 obj2GameObjectRotation=obj2->getGameObjectRotation();


	glm::mat3 obj1BoundindBoxRotationMatrix=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj1GameObjectRotation.z),glm::vec3(0.0f,0.0f,1.0f)));
	glm::mat3 obj2BoundindBoxRotationMatrix=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj2GameObjectRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

	auto mat3abs=[](glm::mat3&m){
		for(GLuint i=0;i<3;i++)
			m[i]=glm::abs(m[i]);
        return m;
	};

	glm::vec3 obj1BoundingBoxMin=-mat3abs(obj1BoundindBoxRotationMatrix)*obj1Collider->getBoundingBoxSize()/2.0f+obj1GameObjectPosition;
	glm::vec3 obj1BoundingBoxMax=mat3abs(obj1BoundindBoxRotationMatrix)*obj1Collider->getBoundingBoxSize()/2.0f+obj1GameObjectPosition;

	glm::vec3 obj2BoundingBoxMin=-mat3abs(obj2BoundindBoxRotationMatrix)*obj2Collider->getBoundingBoxSize()/2.0f+obj2GameObjectPosition;
	glm::vec3 obj2BoundingBoxMax=mat3abs(obj2BoundindBoxRotationMatrix)*obj2Collider->getBoundingBoxSize()/2.0f+obj2GameObjectPosition;

	GLboolean didCollide=GL_FALSE;
	// AABB
	if((obj1BoundingBoxMax.x>obj2BoundingBoxMin.x&&obj1BoundingBoxMin.x<obj2BoundingBoxMax.x)&&
           (obj1BoundingBoxMax.y>obj2BoundingBoxMin.y&&obj1BoundingBoxMin.y<obj2BoundingBoxMax.y) &&
           (obj1BoundingBoxMax.z>obj2BoundingBoxMin.z&&obj1BoundingBoxMin.z<obj2BoundingBoxMax.z)){
		std::cout<<"Kolizja"<<std::endl;
		didCollide=GL_TRUE;
	}


	return didCollide;
}
