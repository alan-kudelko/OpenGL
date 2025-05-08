#include "GL_GameObject.h"

GLS::GL_GameObject::GL_GameObject(glm::vec3 location,glm::vec3 rotation,std::string name){
	_name=name;
	_gameObjectLocation=location;
	_gameObjectRotation=rotation;

	_shapeComponentLocation=_shapeComponentRotation=_shapeComponentScale=nullptr;

	_shapeComponentPtr=nullptr;
	_shaderComponentPtr=nullptr;

	_renderEnable=GL_TRUE;
	_collisionEnable=GL_FALSE;
}
GLS::GL_GameObject::~GL_GameObject(){
	delete _shapeComponentLocation;
	delete _shapeComponentRotation;
	delete _shapeComponentScale;
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
void GLS::GL_GameObject::setShapeComponentScale(glm::vec3 shapeComponentScale){
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

const GLS::GL_Component*GLS::GL_GameObject::getComponent(GLS::GL_ComponentType componentType)const{
	switch(componentType){
		case GLS::GL_ComponentType::GL_SHAPE_Component:
			return _shapeComponentPtr;
		case GLS::GL_ComponentType::GL_SHADER_Component:
			return _shaderComponentPtr;
		case GLS::GL_ComponentType::GL_COLLIDER_Component:
		r	return _colliderComponentPtr;
		default:
		return nullptr;
	}
}
void GLS::GL_GameObject::addComponent(GLS::GL_Component*component){
	if(dynamic_cast<GLS::GL_Shape*>(component)){
		_shapeComponentPtr=dynamic_cast<GLS::GL_Shape*>(component);

		_shapeComponentLocation=new glm::vec3{};
		_shapeComponentRotation=new glm::vec3{};
		_shapeComponentScale=new glm::vec3{100.0f,10.0f,1.0f};
	}
	else if(dynamic_cast<GLS::GL_Shader*>(component)){
		// Overengineered for future development of GLS::GL_SHADER class
		// For now, simple typeid comparison would do the trick
		_shaderComponentPtr=dynamic_cast<GLS::GL_Shader*>(component);
	}
	else if(dynamic_cast<GLS::GL_Collider*>(component){
		_colliderComponentPtr=dynamic_cast<GLS::GL_Collider*>(component);
		// I don't think that collider should be shared among multiple objects
		// I think that better solution is to create new instance of GL_Collider class inside GL_GameObject class
	}
}
