#include "GL_CollisionManager.h"
#include "GL_GameObject.h"
#include "GL_Collider.h"
#include "GL_CollisionResolve.h"

#include <climits>
#include <algorithm>
GLboolean GLS::GL_CollisionManager::_checkAABBCollision(glm::vec2 obj1BoundingBoxMin,glm::vec2 obj1BoundingBoxMax,glm::vec2 obj2BoundingBoxMin,glm::vec2 obj2BoundingBoxMax){
	if((obj1BoundingBoxMax.x>=obj2BoundingBoxMin.x&&obj1BoundingBoxMin.x<=obj2BoundingBoxMax.x)&&
           (obj1BoundingBoxMax.y>=obj2BoundingBoxMin.y&&obj1BoundingBoxMin.y<=obj2BoundingBoxMax.y)){
		return GL_TRUE;
	}
	return GL_FALSE;
}
GLboolean GLS::GL_CollisionManager::_checkSATCollision(glm::vec2* obj1Vertices,GLuint obj1VertCount,
	glm::vec2* obj2Vertices,GLuint obj2VertCount) {
	auto checkAxes=[&](glm::vec2* vertices,GLuint count) {
		for(GLuint i=0; i < count; i++) {
			glm::vec2 p1=glm::vec2(vertices[i]);
			glm::vec2 p2=glm::vec2(vertices[(i + 1) % count]);
			glm::vec2 edge=p2 - p1;
			glm::vec2 axis=glm::normalize(glm::vec2(-edge.y,edge.x));

			std::vector<float> proj1(obj1VertCount);
			std::vector<float> proj2(obj2VertCount);

			for(GLuint j=0; j < obj1VertCount; j++)
				proj1[j]=glm::dot(glm::vec2(obj1Vertices[j]),axis);

			for(GLuint j=0; j < obj2VertCount; j++)
				proj2[j]=glm::dot(glm::vec2(obj2Vertices[j]),axis);

			auto [min1,max1]=std::minmax_element(proj1.begin(),proj1.end());
			auto [min2,max2]=std::minmax_element(proj2.begin(),proj2.end());

			if(*max1 < *min2 || *max2 < *min1)
				return false;
		}
		return true;
	};

	if(!checkAxes(obj1Vertices,obj1VertCount)) return GL_FALSE;
	if(!checkAxes(obj2Vertices,obj2VertCount)) return GL_FALSE;

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

			glm::vec2 contactPoint;
			glm::vec2 normalVector;
			GLfloat penetrationDepth=0.0f;

			glm::vec2 obj1GoLocation=(*it)->getLocation();
			glm::vec3 obj1GoRotation=(*it)->getRotation();		
			glm::vec2 obj1GoScale=(*it)->getScale();

			glm::vec2 obj1ColLocation=(*it)->getColliderComponent()->getLocalLocation();
			glm::vec3 obj1ColRotation=(*it)->getColliderComponent()->getLocalRotation();
			glm::vec2 obj1ColScale=(*it)->getColliderComponent()->getLocalScale();
			
			glm::vec2 obj2GoLocation=(*jt)->getLocation();
			glm::vec3 obj2GoRotation=(*jt)->getRotation();
			glm::vec2 obj2GoScale=(*jt)->getScale();

			glm::vec2 obj2ColLocation=(*jt)->getColliderComponent()->getLocalLocation();
			glm::vec3 obj2ColRotation=(*jt)->getColliderComponent()->getLocalRotation();
			glm::vec2 obj2ColScale=(*jt)->getColliderComponent()->getLocalScale();

			auto mat3abs=[](glm::mat3 m){
				for(GLuint i=0;i<3;i++)
					m[i]=glm::abs(m[i]);
				return m;
			};

			glm::mat3 obj1GoRotationMatrix=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj1GoRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

			glm::vec2 obj1GoScaleNew=mat3abs(obj1GoRotationMatrix)*glm::vec3(obj1GoScale,1.0f);

			glm::mat3 obj2GoRotationMatrix=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj2GoRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

			glm::vec2 obj2GoScaleNew=mat3abs(obj2GoRotationMatrix)*glm::vec3(obj2GoScale,1.0f);

			glm::vec2 obj1ColMin=obj1GoLocation- obj1GoScaleNew /2.0f;
			glm::vec2 obj1ColMax=obj1GoLocation+ obj1GoScaleNew /2.0f;
			
			glm::vec2 obj2ColMin=obj2GoLocation- obj2GoScaleNew /2.0f;
			glm::vec2 obj2ColMax=obj2GoLocation+ obj2GoScaleNew /2.0f;

			// AABB
			if(this->_checkAABBCollision(obj1ColMin,obj1ColMax,obj2ColMin,obj2ColMax)){
				std::cout<<"AABB collision"<<std::endl;
				const GLS::GL_BoxCollider*obj1BoxCollider=dynamic_cast<const GLS::GL_BoxCollider*>(obj1Collider);
				const GLS::GL_BoxCollider*obj2BoxCollider=dynamic_cast<const GLS::GL_BoxCollider*>(obj2Collider);
				if((obj1BoxCollider==nullptr)||(obj2BoxCollider==nullptr))
					return collisionInfoStruct;

				glm::vec2 obj1BoxColliderVertices[4];
				obj1BoxCollider->getBoxVertices(obj1BoxColliderVertices);
				glm::vec2 obj2BoxColliderVertices[4];
				obj2BoxCollider->getBoxVertices(obj2BoxColliderVertices);
				// SAT algorithm
				glm::mat3 model(1.0f);
				for(GLuint i=0;i<4;i++){
					//obj1BoxColliderVertices[i]=glm::translate(model,obj1GoLocation)*glm::rotate(model,glm::radians(obj1GoRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,obj1GoScale)*glm::translate(model,obj1ColLocation)*glm::rotate(model,glm::radians(obj1ColRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,obj1ColScale)*glm::vec4(obj1BoxColliderVertices[i],1.0f);

					//obj2BoxColliderVertices[i]=glm::translate(model,obj2GoLocation)*glm::rotate(model,glm::radians(obj2GoRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,obj2GoScale)*glm::translate(model,obj2ColLocation)*glm::rotate(model,glm::radians(obj2ColRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,obj2ColScale)*glm::vec4(obj2BoxColliderVertices[i],1.0f);

				}
				if(this->_checkSATCollision(obj1BoxColliderVertices,4,obj2BoxColliderVertices,4)){
					GLS::GL_CollisionInfo collisionInfo;
					collisionInfo.obj1=(*it);
					collisionInfo.obj2=(*jt);
					collisionInfo.contactPoint=contactPoint;
					collisionInfo.normalVector=normalVector;
					collisionInfo.penetrationDepth=penetrationDepth;
					collisionInfoStruct.push_back(collisionInfo);
					std::cout << "SAT collision" << std::endl;
				}
			}
		}
	}
	return collisionInfoStruct; // Returns two nullptr if objects did not collide
}
