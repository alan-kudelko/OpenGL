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
			GLS::GL_Collider*obj1Collider=(*it)->getColliderComponent();
			GLS::GL_Collider*obj2Collider=(*jt)->getColliderComponent();

			if(obj1Collider==nullptr)
				return collisionInfoStruct;
			if(obj2Collider==nullptr)
				return collisionInfoStruct;
			if(obj1Collider->getCollisionGroup()!=obj2Collider->getCollisionGroup())
				return collisionInfoStruct;
			if(!(obj1Collider->shouldCollide())&&(obj2Collider->shouldCollide()))
				return collisionInfoStruct;

			glm::vec2 boundingBoxVertices[4]{};

			obj1Collider->getAABBvertices(boundingBoxVertices);

			glm::vec2 obj1BoundingBoxMin=boundingBoxVertices[2];
			glm::vec2 obj1BoundingBoxMax=boundingBoxVertices[0];

			obj2Collider->getAABBvertices(boundingBoxVertices);
			glm::vec2 obj2BoundingBoxMin=boundingBoxVertices[2];
			glm::vec2 obj2BoundingBoxMax=boundingBoxVertices[0];

			// AABB
			if(!this->_checkAABBCollision(obj1BoundingBoxMin,obj1BoundingBoxMax,obj2BoundingBoxMin,obj2BoundingBoxMax)){
				obj1Collider->setRenderColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
				obj2Collider->setRenderColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
				continue;
			}
			obj1Collider->setRenderColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));
			obj2Collider->setRenderColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));
			// Colors are for now

			GLboolean canObj1SAT=GL_FALSE;
			GLboolean canObj2SAT=GL_FALSE;

			canObj1SAT=typeid(*obj1Collider).name()==typeid(GLS::GL_BoxCollider).name();
			if(!canObj1SAT)
				canObj1SAT=typeid(*obj1Collider).name()==typeid(GLS::GL_MeshCollider).name();

			canObj2SAT=typeid(*obj2Collider).name()==typeid(GLS::GL_BoxCollider).name();
			if(!canObj2SAT)
				canObj2SAT=typeid(*obj2Collider).name()==typeid(GLS::GL_MeshCollider).name();

			if(canObj1SAT&&canObj2SAT){
				glm::vec2* obj1Vertices=new glm::vec2[obj1Collider->getVertexCount()];
				glm::vec2* obj2Vertices=new glm::vec2[obj2Collider->getVertexCount()];



			}



			//if(!this->_checkSATCollision()){

			//}



		}
	}
	return collisionInfoStruct; // Returns two nullptr if objects did not collide
}
