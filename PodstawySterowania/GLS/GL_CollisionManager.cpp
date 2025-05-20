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
			
			glm::vec3 obj1ColLocation=(*it)->getColliderComponent()->getLocalLocation();
			glm::vec3 obj1ColRotation=(*it)->getColliderComponent()->getLocalRotation();
			glm::vec3 obj1ColScale=(*it)->getColliderComponent()->getLocalScale();
			
			glm::vec3 obj2GoLocation=(*jt)->getLocation();
			glm::vec3 obj2GoRotation=(*jt)->getRotation();
			glm::vec3 obj2GoScale=(*jt)->getScale();

			glm::vec3 obj2ColLocation=(*jt)->getColliderComponent()->getLocalLocation();
			glm::vec3 obj2ColRotation=(*jt)->getColliderComponent()->getLocalRotation();
			glm::vec3 obj2ColScale=(*jt)->getColliderComponent()->getLocalScale();

			auto mat4abs=[](glm::mat4 m){
				for(GLuint i=0;i<4;i++)
					m[i]=glm::abs(m[i]);
				return m;
			};
			auto getCords=[](glm::mat4 m)->glm::vec3{
				return glm::vec3(m[3][0],m[3][1],m[3][2]);
			};

			glm::vec3 obj1ColMin=obj1GoLocation+obj1ColLocation/obj1GoScale-obj1ColScale*obj1GoScale/2.0f;
			glm::vec3 obj1ColMax=obj1GoLocation+obj1ColLocation/obj1GoScale+obj1ColScale*obj1GoScale/2.0f;
			
			glm::vec3 obj2ColMin=obj2GoLocation+obj2ColLocation/obj2GoScale-obj2ColScale*obj2GoScale/2.0f;
			glm::vec3 obj2ColMax=obj2GoLocation+obj2ColLocation/obj2GoScale+obj2ColScale*obj2GoScale/2.0f;
			
			// For now let's assume that GL_Mesh, GL_Collider and GL_GameObject are not shifted
			//glm::mat4 model=glm::mat4(1.0f);

			//obj1ColMin=getCords(glm::translate(model,obj1GoLocation) *
			//	(glm::rotate(model,glm::radians(obj1GoRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj1GoScale) *
			//	glm::translate(model,obj1ColMin) *
			//	mat4abs(glm::rotate(model,glm::radians(obj1ColRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj1ColScale));

			//obj1ColMax=getCords(glm::translate(model,obj1GoLocation) *
			//	(glm::rotate(model,glm::radians(obj1GoRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj1GoScale) *
			//	glm::translate(model,obj1ColMax) *
			//	mat4abs(glm::rotate(model,glm::radians(obj1ColRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj1ColScale));

			//obj2ColMin=getCords(glm::translate(model,obj2GoLocation) *
			//	(glm::rotate(model,glm::radians(obj2GoRotation.z),glm::vec3(0.0f,0.0f,1.0f)) *
			//	glm::scale(model,obj2GoScale) *
			//	glm::translate(model,obj2ColMin) *
			//	mat4abs(glm::rotate(model,glm::radians(obj2ColRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj2ColScale)));

			//obj2ColMax=getCords(glm::translate(model,obj2GoLocation) *
			//	mat4abs(glm::rotate(model,glm::radians(obj2GoRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj2GoScale) *
			//	glm::translate(model,obj2ColMax) *
			//	mat4abs(glm::rotate(model,glm::radians(obj2ColRotation.z),glm::vec3(0.0f,0.0f,1.0f))) *
			//	glm::scale(model,obj2ColScale));

			// AABB
			if(this->_checkAABBCollision(obj1ColMin,obj1ColMax,obj2ColMin,obj2ColMax)){
				std::cout<<"Kolizja AABB"<<std::endl;

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
	return collisionInfoStruct; // Returns two nullptr if objects did not collide
}
