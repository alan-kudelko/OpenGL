#include "GL_GameObject.h"
#include "GL_Component.h"
#include "GL_Transform.h"
#include "GL_Mesh.h"
#include "GL_Shader.h"
#include "GL_Collider.h"
#include "GL_CollisionBehaviour.h"
#include "GL_PhysicsBody.h"
#include <algorithm>
#include <vector>
#include <climits>

////////////////////////////////////////////////////////////////// GL_GameObject interface
GLuint GLS::GL_GameObject::_GL_GameObjectCounter=0;

GLS::GL_GameObject::GL_GameObject(GLS::GL_Shader*shaderComponent,std::string meshType,glm::vec2 location,glm::vec3 rotation,glm::vec2 scale){
	_GL_GameObjectCounter++;

	_name="GL_GameObject"+_GL_GameObjectCounter;
	_transformComponent=new GLS::GL_Transform(location,rotation,scale);
	_meshComponent=new GLS::GL_Mesh(meshType,glm::vec2(0.0f),glm::vec3(0.0f),glm::vec2(1.0f));
	_colliderComponent=new GLS::GL_BoxCollider(glm::vec2(0.0f),glm::vec3(0.0f),glm::vec2(1.0f));
	_collisionBehaviourComponent=new GLS::GL_CollisionBehaviour(&GLS::behaviourDoNothing);
	_shaderComponent=shaderComponent;

	_shouldDestroy=GL_FALSE;
	_meshComponent->enableRender();
	_physicsComponent=nullptr;
}
GLS::GL_GameObject::GL_GameObject(GLS::GL_Shader* shaderComponent,GLuint polygonCount,glm::vec2 location,glm::vec3 rotation,glm::vec2 scale){
	_GL_GameObjectCounter++;

	_name="GL_GameObject" + _GL_GameObjectCounter;
	_transformComponent=new GLS::GL_Transform(location,rotation,scale);
	_meshComponent=new GLS::GL_Mesh(polygonCount,glm::vec2(0.0f),glm::vec3(0.0f),glm::vec2(1.0f));
	_colliderComponent=new GLS::GL_BoxCollider(glm::vec2(0.0f),glm::vec3(0.0f),glm::vec2(1.0f));
	_collisionBehaviourComponent=new GLS::GL_CollisionBehaviour(&GLS::behaviourDoNothing);
	_shaderComponent=shaderComponent;

	_shouldDestroy=GL_FALSE;
	_meshComponent->enableRender();
	_physicsComponent=nullptr;
}
GLS::GL_GameObject::GL_GameObject(){
	_GL_GameObjectCounter++;

	_name="GL_GameObject"+_GL_GameObjectCounter;

	_transformComponent=nullptr;
	_meshComponent=nullptr;
	_shaderComponent=nullptr;
	_colliderComponent=nullptr;
	_collisionBehaviourComponent=nullptr;
	_physicsComponent=nullptr;

	_shouldDestroy=GL_FALSE;
}
GLS::GL_GameObject::~GL_GameObject(){
	delete _transformComponent;
	delete _meshComponent;
	delete _colliderComponent;
	delete _collisionBehaviourComponent;
	_GL_GameObjectCounter--;
}
////////////////////////////////////////////////////////////////// GL_Transform interface
glm::vec2 GLS::GL_GameObject::getLocation()const{
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _transformComponent->getLocation();
}
glm::vec3 GLS::GL_GameObject::getRotation()const{
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _transformComponent->getRotation();
}
glm::vec2 GLS::GL_GameObject::getScale()const{
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _transformComponent->getScale();
}
void GLS::GL_GameObject::setLocation(glm::vec2 location){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->setLocation(location);

	if(_colliderComponent==nullptr)
		return;
	this->_recalculateAABB();
}
void GLS::GL_GameObject::setRotation(glm::vec3 rotation){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->setRotation(rotation);
	if(_colliderComponent==nullptr)
		return;
	this->_recalculateAABB();
}
void GLS::GL_GameObject::setScale(glm::vec2 scale) {
	if (_transformComponent == nullptr) {
		std::string exceptionText = "Transform component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->setScale(scale);
	if(_colliderComponent==nullptr)
		return;
	this->_recalculateAABB();
}
void GLS::GL_GameObject::move(glm::vec2 delta){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->move(delta);
	if(_colliderComponent==nullptr)
		return;
	this->_recalculateAABB();
}
void GLS::GL_GameObject::rotate(glm::vec3 delta){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->rotate(delta);
	if(_colliderComponent==nullptr)
		return;
	this->_recalculateAABB();
}
void GLS::GL_GameObject::scaleBy(glm::vec2 delta){
	if(_transformComponent == nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->scaleBy(delta);
	if(_colliderComponent==nullptr)
		return;
	this->_recalculateAABB();
}
////////////////////////////////////////////////////////////////// GL_Physics interface
glm::vec2 GLS::GL_GameObject::getGameObjectLinearVelocity()const{
	if(_physicsComponent==nullptr){
		std::string exceptionText="Physics component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _physicsComponent->getLinearVelocity();
}
glm::vec3 GLS::GL_GameObject::getGameObjectAngularVelocity()const{
	if(_physicsComponent==nullptr){
		std::string exceptionText="Physics component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _physicsComponent->getAngularVelocity();
}
void GLS::GL_GameObject::setGameObjectLinearVelocity(glm::vec2 gameObjectLinearVelocity){
	if(_physicsComponent==nullptr){
		std::string exceptionText="Physics component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_physicsComponent->setLinearVelocity(gameObjectLinearVelocity);
}
void GLS::GL_GameObject::setGameObjectAngularVelocity(glm::vec3 gameObjectRotationalVelocity){
	if(_physicsComponent==nullptr){
		std::string exceptionText="Physics component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_physicsComponent->setAngularVelocity(gameObjectRotationalVelocity);
}
void GLS::GL_GameObject::updateGameObjectLocation(GLfloat deltaTime){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	} // For now, velocities also must exist but in GL_Physics
	if(_physicsComponent==nullptr){
		std::string exceptionText="Physics component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	glm::vec2 positionIntegral=_physicsComponent->getLinearVelocity()*deltaTime;
	glm::vec3 rotationIntegral=_physicsComponent->getAngularVelocity()*deltaTime;

	_transformComponent->move(positionIntegral);
	_transformComponent->rotate(rotationIntegral);
}
////////////////////////////////////////////////////////////////// GL_CollisionBehaviour interface (in near future)
void GLS::GL_GameObject::markForDestruction(){
	_shouldDestroy=GL_TRUE;
}
void GLS::GL_GameObject::unmarkForDestruction(){
	_shouldDestroy=GL_FALSE;
}
GLboolean GLS::GL_GameObject::shouldDestroy()const{
	return _shouldDestroy;
}
////////////////////////////////////////////////////////////////// GL_Shape interface
void GLS::GL_GameObject::enableRender(){
	if(_meshComponent==nullptr){
		std::string exceptionText="Mesh component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _meshComponent->enableRender();
}
void GLS::GL_GameObject::disableRender(){
	if(_meshComponent==nullptr){
		std::string exceptionText="Mesh component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _meshComponent->disableRender();
}
GLboolean GLS::GL_GameObject::shouldRender()const{
	if(_meshComponent==nullptr){
		std::string exceptionText="Mesh component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _meshComponent->shouldRender();
}
////////////////////////////////////////////////////////////////// GL_Collider interface
void GLS::GL_GameObject::_recalculateAABB(){
	GLS::GL_Transform colliderLocalTransform=_colliderComponent->getLocalTransform();

	glm::mat4 model(1.0f);

	model=glm::translate(model,glm::vec3(_transformComponent->getLocation(),0.0f)) *
		glm::rotate(model,glm::radians(_transformComponent->getRotation().z),glm::vec3(0.0f,0.0f,1.0f)) *
		glm::scale(model,glm::vec3(_transformComponent->getScale(),1.0f)) *
		glm::translate(model,glm::vec3(colliderLocalTransform.getLocation(),0.0f)) *
		glm::rotate(model,glm::radians(colliderLocalTransform.getRotation().z),glm::vec3(0.0f,0.0f,1.0f)) *
		glm::scale(model,glm::vec3(colliderLocalTransform.getScale(),1.0f));

	std::vector<glm::vec2>newAABBVertices{
		glm::vec2(0.5f,0.5f),
		glm::vec2(0.5f,-0.5f),
		glm::vec2(-0.5f,-0.5f),
		glm::vec2(-0.5f,0.5f)
	};

	for(GLuint i=0;i < 4;i++){
		newAABBVertices[i]=glm::vec2(model * glm::vec4(newAABBVertices[i],0.0f,1.0f));
	}

	glm::vec2 min{std::numeric_limits<float>::max(),std::numeric_limits<float>::max()};
	glm::vec2 max{std::numeric_limits<float>::min(),std::numeric_limits<float>::min()};

	for(GLuint i=0;i<newAABBVertices.size();i++) {
		min.x=std::min(min.x,newAABBVertices[i].x);
		min.y=std::min(min.y,newAABBVertices[i].y);
		max.x=std::max(max.x,newAABBVertices[i].x);
		max.y=std::max(max.y,newAABBVertices[i].y);
	}
	newAABBVertices[0]=glm::vec2(max.x,max.y);
	newAABBVertices[1]=glm::vec2(max.x,min.y);
	newAABBVertices[2]=glm::vec2(min.x,min.y);
	newAABBVertices[3]=glm::vec2(min.x,max.y);
	
	_colliderComponent->setAABBvertices(newAABBVertices);
}
void GLS::GL_GameObject::enableCollisions(){
	if(_colliderComponent==nullptr){
		std::string exceptionText="Collider component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_colliderComponent->enableCollisions();
}
void GLS::GL_GameObject::disableCollisions(){
	if(_colliderComponent==nullptr){
		std::string exceptionText="Collider component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_colliderComponent->disableCollisions();
}
GLboolean GLS::GL_GameObject::shouldCollide()const{
	if(_colliderComponent==nullptr){
		std::string exceptionText="Collider component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _colliderComponent->shouldCollide();
}
////////////////////////////////////////////////////////////////// GL_GameObject interface for component management
GLS::GL_Transform*GLS::GL_GameObject::getTransformComponent(){
	return _transformComponent;
}
GLS::GL_Mesh*GLS::GL_GameObject::getMeshComponent(){
	return _meshComponent;
}
const GLS::GL_Shader*GLS::GL_GameObject::getShaderComponent()const{
	return _shaderComponent;
}
GLS::GL_Collider*GLS::GL_GameObject::getColliderComponent(){
	return _colliderComponent;
}
GLS::GL_CollisionBehaviour*GLS::GL_GameObject::getCollisionBehaviourComponent(){
	return _collisionBehaviourComponent;
}
void GLS::GL_GameObject::createTransformComponent(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale){
	_transformComponent=new GLS::GL_Transform(location,rotation,scale);
}
void GLS::GL_GameObject::createMeshComponent(std::string meshType,glm::vec2 location,glm::vec3 rotation, glm::vec2 scale){
	_meshComponent=new GLS::GL_Mesh(meshType);
	_meshComponent->setLocalLocation(location);
	_meshComponent->setLocalRotation(rotation);
	_meshComponent->setLocalScale(scale);
}
void GLS::GL_GameObject::assignShaderComponent(GLS::GL_Shader*component){
	_shaderComponent=component;
}
void GLS::GL_GameObject::createCollisionComponent(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,std::string colliderType,GLuint collisionGroup){
	if(colliderType=="BoxCollider"){
		_colliderComponent=new GLS::GL_BoxCollider(location,rotation,scale,collisionGroup);
	}
	else if(colliderType=="SphereCollider"){
		std::string exceptionText="Sphere collider not added yet in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	else if(colliderType=="MeshCollider"){
		if(_meshComponent == nullptr){
			std::string exceptionText="Cannot create GL_MeshCollider if mesh component is missing in GL_GameObject " + _name;
			throw std::runtime_error(exceptionText.c_str());
		}
		_colliderComponent=new GLS::GL_MeshCollider(_meshComponent->getVertices(),_meshComponent->getVertCount(),location,rotation,scale,collisionGroup);
	}
	else{
		std::string exceptionText="Trying to create undefined collider component in GL_GameObject " + _name+" Collider type "+colliderType;
		throw std::runtime_error(exceptionText.c_str());
	}
}
void GLS::GL_GameObject::createCollisionBehaviourComponent(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)){
	_collisionBehaviourComponent=new GLS::GL_CollisionBehaviour(behaviourFunPtr);
}
