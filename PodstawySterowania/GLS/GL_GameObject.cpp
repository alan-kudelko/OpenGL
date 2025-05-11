#include "GL_GameObject.h"


////////////////////////////////////////////////////////////////// GL_GameObject interface
glm::vec3 GLS::GL_GameObject::_normalizeAngles(glm::vec3){
	glm::vec3 normalizedAngles;
	//lambda
	return normalizedAngles;
}
GLS::GL_GameObject::GL_GameObject(glm::vec3 location,glm::vec3 rotation,std::string name){
	_name=name;
	_gameObjectLocation=location;
	_gameObjectRotation=rotation;

	_shapeComponentLocation=_shapeComponentRotation=_shapeComponentScale=nullptr;

	_shapeComponentPtr=nullptr;
	_shaderComponentPtr=nullptr;
	_colliderComponentPtr=nullptr;

	_renderEnable=GL_TRUE;
}
GLS::GL_GameObject::~GL_GameObject(){
	delete _shapeComponentLocation;
	delete _shapeComponentRotation;
	delete _shapeComponentScale;
	delete _colliderComponentPtr;
}
glm::vec3 GLS::GL_GameObject::getGameObjectLocation()const{
	return _gameObjectLocation;
}
glm::vec3 GLS::GL_GameObject::getGameObjectRotation()const{
	return _gameObjectRotation;
}
void GLS::GL_GameObject::setGameObjectLocation(glm::vec3 gameObjectLocation){
	_gameObjectLocation=gameObjectLocation;
}
void GLS::GL_GameObject::setGameObjectRotation(glm::vec3 gameObjectRotation){
	_gameObjectRotation=gameObjectRotation;

	if(_gameObjectRotation.x>360.0f)
		_gameObjectRotation.x-=360.0f;
	if(_gameObjectRotation.y>360.0f)
		_gameObjectRotation.y-=360.0f;
	if(_gameObjectRotation.z>360.0f)
		_gameObjectRotation.z-=360.0f;

	if(_gameObjectRotation.x<-360.0f)
		_gameObjectRotation.x+=360.0f;
	if(_gameObjectRotation.y<-360.0f)
		_gameObjectRotation.y+=360.0f;
	if(_gameObjectRotation.z<-360.0f)
		_gameObjectRotation.z+=360.0f;
	
	_colliderComponentPtr->updateBoundingBoxSize(_gameObjectRotation);
	// Change to modulo
	// Place this checking code in other method as all rotations should check for cycling values
}
void GLS::GL_GameObject::updateGameObjectLocation(glm::vec3 gameObjectLocation){
	_gameObjectLocation+=gameObjectLocation;
}
void GLS::GL_GameObject::updateGameObjectRotation(glm::vec3 gameObjectRotation){
	_gameObjectRotation+=gameObjectRotation;
	_colliderComponentPtr->updateBoundingBoxSize(_gameObjectRotation);
}
////////////////////////////////////////////////////////////////// GL_Shape interface 
glm::vec3 GLS::GL_GameObject::getShapeComponentLocation()const{
	if(_shapeComponentPtr!=nullptr)
		return *_shapeComponentLocation;
	return glm::vec3{};
}
glm::vec3 GLS::GL_GameObject::getShapeComponentRotation()const{
	if(_shapeComponentPtr!=nullptr)
		return *_shapeComponentRotation;
	return glm::vec3{};
}
glm::vec3 GLS::GL_GameObject::getShapeComponentSize()const{
	if(_shapeComponentPtr!=nullptr)
		return *_shapeComponentScale;
	return glm::vec3{};
}
void GLS::GL_GameObject::setShapeComponentLocation(glm::vec3 shapeComponentLocation){
	if(_shapeComponentPtr!=nullptr)
		(*_shapeComponentLocation)=shapeComponentLocation;
}
void GLS::GL_GameObject::setShapeComponentRotation(glm::vec3 shapeComponentRotation){
	if(_shapeComponentPtr!=nullptr)
		(*_shapeComponentRotation)=shapeComponentRotation;
}
void GLS::GL_GameObject::setShapeComponentSize(glm::vec3 shapeComponentScale){
	if(_shapeComponentPtr!=nullptr)	
		(*_shapeComponentScale)=shapeComponentScale;
}
void GLS::GL_GameObject::enableShapeComponentRender(){
	_renderEnable=GL_TRUE;
}
void GLS::GL_GameObject::disableShapeComponentRender(){
	_renderEnable=GL_FALSE;
}
GLboolean GLS::GL_GameObject::shouldShapeComponentRender()const{
	return _renderEnable;
}
////////////////////////////////////////////////////////////////// GL_Collider interface
void GLS::GL_GameObject::setColliderComponentLocation(glm::vec3 location){
	if(_colliderComponentPtr!=nullptr)
		_colliderComponentPtr->setBoundingBoxLocation(location);
}
void GLS::GL_GameObject::setColliderComponentSize(glm::vec3 size){
	if(_colliderComponentPtr!=nullptr){
		_colliderComponentPtr->setBoundingBoxSize(size);
		_colliderComponentPtr->updateBoundingBoxSize(_gameObjectRotation);
	}
}
void GLS::GL_GameObject::enableColliderComponentCollisions(){
	if(_colliderComponentPtr!=nullptr)
		_colliderComponentPtr->enableCollisions();
}
void GLS::GL_GameObject::disableColliderComponentCollisions(){
	if(_colliderComponentPtr!=nullptr)
		_colliderComponentPtr->disableCollisions();
}
GLboolean GLS::GL_GameObject::shouldColliderComponentCollide()const{
	if(_colliderComponentPtr!=nullptr)
		return _colliderComponentPtr->shouldCollide();
	return GL_FALSE;
}
////////////////////////////////////////////////////////////////// GL_GameObject interface for component management
const GLS::GL_Shape*GLS::GL_GameObject::getShapeComponent()const{
	return _shapeComponentPtr;
}
const GLS::GL_Shader*GLS::GL_GameObject::getShaderComponent()const{
	return _shaderComponentPtr;
}
const GLS::GL_Collider*GLS::GL_GameObject::getColliderComponent()const{
	return _colliderComponentPtr;
}
void GLS::GL_GameObject::assignShapeComponent(GLS::GL_Shape*component){
	_shapeComponentLocation=new glm::vec3{};
	_shapeComponentRotation=new glm::vec3{};
	_shapeComponentScale=new glm::vec3{1.0f,1.0f,1.0f};
	_shapeComponentPtr=component;
}
void GLS::GL_GameObject::assignShaderComponent(GLS::GL_Shader*component){
	_shaderComponentPtr=component;
}
void GLS::GL_GameObject::createCollisionComponent(glm::vec3 location,glm::vec3 size,GLuint collisionGroup){
	_colliderComponentPtr=new GLS::GL_Collider(location,size,collisionGroup);
}
