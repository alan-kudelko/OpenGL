#include "GL_GameObject.h"

GLS::GL_GameObject::GL_GameObject(glm::vec3 location,glm::vec3 rotation,std::string name){
	_name=name;
	_gameObjectLocation=location;
	_gameObjectRotation=rotation;

	_shapeComponentLocation=_shapeComponentRotation=_shapeComponentScale=nullptr;

	_shapeComponentPtr=nullptr;
	_shaderComponentPtr=nullptr;
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
	(*shapeComponentLocation)=shapeComponentLocation;
}
void GLS::GL_GameObject::setShapeComponentRotation(glm::vec3 shapeComponentRotation){
	(*shapeComponentRotation)=shapeComponentRotation;
}
void GLS::GL_GameObject::setShapeComponentScale(glm::vec3 shapeComponentScale){
	(*shapeComponentScale)=shapeComponentScale;
}


const GLS::GL_Component*GLS::GL_GameObject::getComponent(GLS::GL_Component componentType)const{
	return _shapeComponentPtr;
	return _shaderComponentPtr;
}
void GLS::GL_GameObject::addComponent(GLS::GL_Component*componentType){
	//Tutaj warto zwrocic uwage na to, ze klasa nie musi zadnego obiektu przechowywac
	//Dlaczego?
	//Kazdy ksztalt moze zostac stworzony raz
	//Co oznacza ze obiekt jedynie bedzie przechowywac wskaznik do tego obiektu
	//A shader sobie przeliczy wszystko tak jak trzeba
	//Wiec jest tu miejsce na optymalizacje

	//Na razie chyba zostawie to z tworzeniem nowych instacji klas poza klasa shader oraz texture ale w przyszlosci warto to zmienic
}
void renderObject()const{
	if(shaderComponentPtr==nullptr)
		return;


}
