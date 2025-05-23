#include "GL_CollisionManager.h"
#include "GL_GameObject.h"
#include "GL_Collider.h"
#include "GL_CollisionResolve.h"

GLboolean GLS::GL_CollisionManager::_checkAABBCollision(glm::vec3 obj1BoundingBoxMin,glm::vec3 obj1BoundingBoxMax,glm::vec3 obj2BoundingBoxMin,glm::vec3 obj2BoundingBoxMax){
	if((obj1BoundingBoxMax.x>=obj2BoundingBoxMin.x&&obj1BoundingBoxMin.x<=obj2BoundingBoxMax.x)&&
           (obj1BoundingBoxMax.y>=obj2BoundingBoxMin.y&&obj1BoundingBoxMin.y<=obj2BoundingBoxMax.y)&&
           (obj1BoundingBoxMax.z>=obj2BoundingBoxMin.z&&obj1BoundingBoxMin.z<=obj2BoundingBoxMax.z)){
		return GL_TRUE;
	}
	return GL_FALSE;
}
GLboolean GLS::GL_CollisionManager::_checkSATCollision(glm::vec3 obj1Vertices,GLuint obj1VertCount,glm::vec3 obj2Vertices,GLuint obj2VertCount){

	return GL_TRUE;
}

GLS::GL_CollisionManager::GL_CollisionManager(){

}
GLS::GL_CollisionManager::~GL_CollisionManager(){

}
std::vector<GLS::GL_CollisionInfo>GLS::GL_CollisionManager::checkCollisions(std::vector<GLS::GL_GameObject*>gameObjects){
	// Checking if these two objects have GL_Collider component
	// Checking if two objects are in the same collisionGroup
	std::vector<GLS::GL_CollisionInfo>collisionInfoStruct;
	for(auto it=gameObjects.begin()+1;it!=gameObjects.end();++it){
		for(auto jt=gameObjects.begin();jt!=it;++jt){
			const GLS::GL_Collider*obj1Collider=(*it)->getColliderComponent();
			const GLS::GL_Collider*obj2Collider=(*jt)->getColliderComponent();

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
			GLfloat penetrationDepth=0.0f;

			glm::vec3 obj1GoLocation=(*it)->getLocation();
			glm::vec3 obj1GoRotation=(*it)->getRotation();		
			glm::vec3 obj1GoScale=(*it)->getScale();

			glm::vec3 obj1ColScale=(*it)->getColliderComponent()->getLocalScale();
			
			glm::vec3 obj2GoLocation=(*jt)->getLocation();
			glm::vec3 obj2GoRotation=(*jt)->getRotation();
			glm::vec3 obj2GoScale=(*jt)->getScale();

			glm::vec3 obj2ColScale=(*it)->getColliderComponent()->getLocalScale();

			auto mat3abs=[](glm::mat3 m){
				for(GLuint i=0;i<3;i++)
					m[i]=glm::abs(m[i]);
				return m;
			};

			glm::mat3 obj1GoRotationMatrix=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj1GoRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

			obj1GoScale=mat3abs(obj1GoRotationMatrix)*obj1GoScale;

			glm::mat3 obj2GoRotationMatrix=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj2GoRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

			obj2GoScale=mat3abs(obj2GoRotationMatrix)*obj2GoScale;

			glm::vec3 obj1ColMin=obj1GoLocation-obj1GoScale/2.0f;
			glm::vec3 obj1ColMax=obj1GoLocation+obj1GoScale/2.0f;
			
			glm::vec3 obj2ColMin=obj2GoLocation-obj2GoScale/2.0f;
			glm::vec3 obj2ColMax=obj2GoLocation+obj2GoScale/2.0f;

			// AABB
			if(this->_checkAABBCollision(obj1ColMin,obj1ColMax,obj2ColMin,obj2ColMax)){
				std::cout<<"AABB collision"<<std::endl;
				// SAT algorithm
				if(this->_checkSATCollision()){
					GLS::GL_CollisionInfo collisionInfo;
					collisionInfo.obj1=(*it);
					collisionInfo.obj2=(*jt);
					collisionInfo.contactPoint=contactPoint;
					collisionInfo.normalVector=normalVector;
					collisionInfo.penetrationDepth=penetrationDepth;
					collisionInfoStruct.push_back(collisionInfo);
				}
			}
		}
	}
	return collisionInfoStruct; // Returns two nullptr if objects did not collide
}
