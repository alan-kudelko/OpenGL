#include "GL_GameObject.h"

GLS::GL_GameObject::GL_GameObject(glm::vec3 location,glm::vec3 rotation,std::string name){
	_name=name;
	_location=location;
	_rotation=rotation;

	_shapeComponent=nullptr;
	_shaderComponentPtr=nullptr;
}
GLS::GL_GameObject::~GL_GameObject(){
	delete[]_shapeComponent;
}
glm::vec3 GLS::GL_GameObject::getLocation()const{
	return _location;
}
glm::vec3 GLS::GL_GameObject::getRotation()const{
	return _rotation;
}
const GLS::GL_Component&GLS::GL_GameObject::getComponent(GLS::GL_Component componentType)const{
	return *_shapeComponent;
	return *_shaderComponentPtr;
}
GLS::GL_Component*GLS::GL_GameObject::createComponent(GLS::GL_Component componentType){

}
