#include "GL_GameObject.h"

GLS::GL_GameObject::GL_GameObject(glm::vec3 location,glm::vec3 rotation,std::string name){
	_name=name;
	_gameObjectLocation=location;
	_gameObjectRotation=rotation;

	_shapeComponentLocation=_shapeComponentRotation=_shapeComponentScale=nullptr;

	_shapeComponentPtr=nullptr;
	_shaderComponentPtr=nullptr;
	_colliderComponentPtr=nullptr;

	_renderEnable=GL_TRUE;
	_collisionEnable=GL_FALSE;
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
glm::vec3 GLS::GL_GameObject::getShapeComponentLocation()const{
	return *_shapeComponentLocation;
}
glm::vec3 GLS::GL_GameObject::getShapeComponentRotation()const{
	return *_shapeComponentRotation;
}
glm::vec3 GLS::GL_GameObject::getShapeComponentScale()const{
	return *_shapeComponentScale;
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
	// Change to modulo
	// Place this checking code in other method as all rotations should check for cycling values
}
void GLS::GL_GameObject::updateGameObjectLocation(glm::vec3 gameObjectLocation){
	_gameObjectLocation+=gameObjectLocation;
}
void GLS::GL_GameObject::updateGameObjectRotation(glm::vec3 gameObjectRotation){
	_gameObjectRotation+=gameObjectRotation;
}
void GLS::GL_GameObject::setShapeComponentLocation(glm::vec3 shapeComponentLocation){
	(*_shapeComponentLocation)=shapeComponentLocation;
}
void GLS::GL_GameObject::setShapeComponentRotation(glm::vec3 shapeComponentRotation){
	(*_shapeComponentRotation)=shapeComponentRotation;
}
void GLS::GL_GameObject::setShapeComponentSize(glm::vec3 shapeComponentScale){
	(*_shapeComponentScale)=shapeComponentScale;
}
GLboolean GLS::GL_GameObject::shouldRender()const{
	return _renderEnable;
}
void GLS::GL_GameObject::enableRender(){
	_renderEnable=GL_TRUE;
}
void GLS::GL_GameObject::disableRender(){
	_renderEnable=GL_FALSE;
}
GLboolean GLS::GL_GameObject::shouldCollide()const{
	return _collisionEnable;
}
void GLS::GL_GameObject::enableCollisions(){
	_collisionEnable=GL_TRUE;
}
void GLS::GL_GameObject::disableCollisions(){
	_collisionEnable=GL_FALSE;
}
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
