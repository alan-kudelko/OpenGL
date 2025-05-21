#include "GL_GameObject.h"
#include "GL_Component.h"
#include "GL_Transform.h"
#include "GL_Mesh.h"
#include "GL_Shader.h"
#include "GL_Collider.h"
#include "GL_CollisionBehaviour.h"

////////////////////////////////////////////////////////////////// GL_GameObject interface
GLuint GLS::GL_GameObject::_GL_GameObjectCounter=0;

GLS::GL_GameObject::GL_GameObject(GLS::GL_Shader*shaderComponent,std::string meshType,glm::vec3 location,glm::vec3 rotation,glm::vec3 scale){
	_GL_GameObjectCounter++;

	_name="GL_GameObject"+_GL_GameObjectCounter;
	_transformComponent=new GLS::GL_Transform(location,rotation,scale);
	_meshComponent=new GLS::GL_Mesh(meshType,glm::vec3(0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
	_colliderComponent=new GLS::GL_Collider(glm::vec3(0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
	_collisionBehaviourComponent=new GLS::GL_CollisionBehaviour(&GLS::behaviourDoNothing);
	_shaderComponent=shaderComponent;

	_gameObjectLinearVelocity=glm::vec3{};
	_gameObjectRotationalVelocity=glm::vec3{}; // These two assignments will be moved to GL_Physics

	_shouldDestroy=GL_FALSE;
	_meshComponent->enableRender();
}
GLS::GL_GameObject::GL_GameObject(GLS::GL_Shader* shaderComponent,GLuint polygonCount,glm::vec3 location,glm::vec3 rotation,glm::vec3 scale){
	_GL_GameObjectCounter++;

	_name="GL_GameObject" + _GL_GameObjectCounter;
	_transformComponent=new GLS::GL_Transform(location,rotation,scale);
	_meshComponent=new GLS::GL_Mesh(polygonCount,glm::vec3(0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
	_colliderComponent=new GLS::GL_Collider(glm::vec3(0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
	_collisionBehaviourComponent=new GLS::GL_CollisionBehaviour(&GLS::behaviourDoNothing);
	_shaderComponent=shaderComponent;

	_gameObjectLinearVelocity=glm::vec3{};
	_gameObjectRotationalVelocity=glm::vec3{}; // These two assignments will be moved to GL_Physics

	_shouldDestroy=GL_FALSE;
	_meshComponent->enableRender();
}
GLS::GL_GameObject::GL_GameObject(){
	_GL_GameObjectCounter++;

	_name="GL_GameObject"+_GL_GameObjectCounter;

	_transformComponent=nullptr;
	_meshComponent=nullptr;
	_shaderComponent=nullptr;
	_colliderComponent=nullptr;
	_collisionBehaviourComponent=nullptr;

	_gameObjectLinearVelocity=glm::vec3{};
	_gameObjectRotationalVelocity=glm::vec3{}; // These two assignments will be moved to GL_Physics

	_shouldDestroy=GL_FALSE;
}
GLS::GL_GameObject::~GL_GameObject(){
	delete _shapeComponentLocation;
	delete _shapeComponentRotation;
	delete _shapeComponentScale;
	delete _transformComponent;
	delete _meshComponent;
	delete _colliderComponent;
	delete _collisionBehaviourComponent;
	_GL_GameObjectCounter--;
}
////////////////////////////////////////////////////////////////// GL_Transform interface
glm::vec3 GLS::GL_GameObject::getLocation()const{
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
glm::vec3 GLS::GL_GameObject::getScale()const{
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	return _transformComponent->getScale();
}
void GLS::GL_GameObject::setLocation(glm::vec3 location){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->setLocation(location);
}
void GLS::GL_GameObject::setRotation(glm::vec3 rotation){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->setRotation(rotation);
	_colliderComponent->updateBoundingBoxSize(_transformComponent->getRotation()); // Rotation will be normalzied by GL_Transform object
}
void GLS::GL_GameObject::setScale(glm::vec3 scale) {
	if (_transformComponent == nullptr) {
		std::string exceptionText = "Transform component is missing in GL_GameObject " + _name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->setScale(scale);
}
void GLS::GL_GameObject::move(glm::vec3 delta){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->move(delta);
}
void GLS::GL_GameObject::rotate(glm::vec3 delta){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	}
	_transformComponent->rotate(delta);
	_colliderComponent->updateBoundingBoxSize(_transformComponent->getRotation()); // Rotation will be normalzied by GL_Transform object
}
////////////////////////////////////////////////////////////////// GL_Physics interface (in near future)
glm::vec3 GLS::GL_GameObject::getGameObjectLinearVelocity()const{
	return _gameObjectLinearVelocity;
}
glm::vec3 GLS::GL_GameObject::getGameObjectRotationalVelocity()const{
	return _gameObjectRotationalVelocity;
}
void GLS::GL_GameObject::setGameObjectLinearVelocity(glm::vec3 gameObjectLinearVelocity){
	_gameObjectLinearVelocity=gameObjectLinearVelocity;
}
void GLS::GL_GameObject::setGameObjectRotationalVelocity(glm::vec3 gameObjectRotationalVelocity){
	_gameObjectRotationalVelocity=gameObjectRotationalVelocity;
}
void GLS::GL_GameObject::updateGameObjectLocation(GLfloat deltaTime){
	if(_transformComponent==nullptr){
		std::string exceptionText="Transform component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	} // For now, velocities also must exist but in GL_Physics
	glm::vec3 positionIntegral=_gameObjectLinearVelocity*deltaTime;
	glm::vec3 rotationIntegral=_gameObjectRotationalVelocity*deltaTime;

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
void GLS::GL_GameObject::enableCollisions(){
	if(_colliderComponent==nullptr){
		std::string exceptionText="Collider component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	} // For now, velocities also must exist but in GL_Physics
	_colliderComponent->enableCollisions();
}
void GLS::GL_GameObject::disableCollisions(){
	if(_colliderComponent==nullptr){
		std::string exceptionText="Collider component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	} // For now, velocities also must exist but in GL_Physics
	_colliderComponent->disableCollisions();
}
GLboolean GLS::GL_GameObject::shouldCollide()const{
	if(_colliderComponent==nullptr){
		std::string exceptionText="Collider component is missing in GL_GameObject "+_name;
		throw std::runtime_error(exceptionText.c_str());
	} // For now, velocities also must exist but in GL_Physics
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
void GLS::GL_GameObject::createTransformComponent(glm::vec3 location,glm::vec3 rotation,glm::vec3 scale){
	_transformComponent=new GLS::GL_Transform(location,rotation,scale);
}
void GLS::GL_GameObject::createMeshComponent(std::string meshType,glm::vec3 location,glm::vec3 rotation, glm::vec3 scale){
	_shapeComponentLocation=new glm::vec3{};
	_shapeComponentRotation=new glm::vec3{};
	_shapeComponentScale=new glm::vec3{1.0f,1.0f,1.0f};
	_meshComponent=new GLS::GL_Mesh(meshType);
}
void GLS::GL_GameObject::assignShaderComponent(GLS::GL_Shader*component){
	_shaderComponent=component;
}
void GLS::GL_GameObject::createCollisionComponent(glm::vec3 location,glm::vec3 rotation,glm::vec3 size,GLuint collisionGroup){
	_colliderComponent=new GLS::GL_Collider(location,rotation,size,collisionGroup);
}
void GLS::GL_GameObject::createCollisionBehaviourComponent(void(*behaviourFunPtr)(GLS::GL_GameObject*,GLS::GL_GameObject*)){
	_collisionBehaviourComponent=new GLS::GL_CollisionBehaviour(behaviourFunPtr);
}
