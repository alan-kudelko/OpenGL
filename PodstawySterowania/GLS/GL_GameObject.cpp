#include "GL_GameObject.h"

GLS::GL_GameObject::GL_GameObject(glm::vec3 location,glm::vec3 rotation,std::string name){
	_name=name;
	_gameObjectLocation=location;
	_gameObjectRotation=rotation;

	_shapeComponentLocation=_shapeComponentRotation=_shapeComponentScale=nullptr;

	_shapeComponentPtr=nullptr;
	_shaderComponentPtr=nullptr;

	_renderEnable=GL_TRUE;
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
	_gameObjectLocation+=gameObjectLocation;
}
void GLS::GL_GameObject::setGameObjectRotation(glm::vec3 gameObjectRotation){
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
const GLS::GL_Component*GLS::GL_GameObject::getComponent(GLS::GL_ComponentType componentType)const{
	switch(componentType){
		case GLS::GL_ComponentType::GL_SHAPE_Component:
			return _shapeComponentPtr;

		case GLS::GL_ComponentType::GL_SHADER_Component:
			return _shapeComponentPtr;

		default:
		return nullptr;
	}
}
void GLS::GL_GameObject::addComponent(GLS::GL_Component*component){
	if(dynamic_cast<GLS::GL_SHAPE*>(component)){
		std::cout<<"Tak, to GL_SHAPE"<<std::endl;
		_shapeComponentPtr=dynamic_cast<GLS::GL_SHAPE*>(component);
	}
	else if(dynamic_cast<GLS::GL_SHADER*>(component)){
		// Overengineered for future development of GLS::GL_SHADER class
		// For now, simple typeid comparison would do the trick
		std::cout<<"Tak, to GL_SHADER"<<std::endl;
		_shaderComponentPtr=dynamic_cast<GLS::GL_SHADER*>(component);
	}
}
void GLS::GL_GameObject::renderObject()const{
	if(_shaderComponentPtr==nullptr)
		return;
	if(_shapeComponentPtr==nullptr)
		return;
	// Temporary for debugging
	glm::mat4 model=glm::mat4(1.0f);
	model=glm::translate(model,glm::vec3(299.5f,499.5f,0.0f))*glm::rotate(model,glm::radians(0.0f),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,glm::vec3(90.0f,10.0f,1.0f));

    glm::mat4 projection=glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, 1.0f, -1.0f);
	glm::mat4 mvp=projection*model;

	glUniformMatrix4fv(glGetUniformLocation(_shaderComponentPtr->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(_shaderComponentPtr->getShaderID(),"model"),1,GL_FALSE,glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(_shaderComponentPtr->getShaderID(),"mvp"),1,GL_FALSE,glm::value_ptr(mvp));

	glUseProgram(_shaderComponentPtr->getShaderID());
	glBindVertexArray(_shapeComponentPtr->getVAO());
	glDrawElements(GL_TRIANGLES,_shapeComponentPtr->getIndicesN(),GL_UNSIGNED_INT,0);
}
