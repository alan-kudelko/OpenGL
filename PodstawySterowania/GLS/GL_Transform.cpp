#include "GL_Transform.h"

glm::vec3 GLS::GL_Transform::normalizeAngles(glm::vec3 rotation){
    glm::vec3 normRotation;
	normRotation.x=fmod(fmod(rotation.x,360.0f)+360.0f,360.0f);
    normRotation.y=fmod(fmod(rotation.y,360.0f)+360.0f,360.0f);
    normRotation.z=fmod(fmod(rotation.z,360.0f)+360.0f,360.0f);
    return normRotation;
}
GLS::GL_Transform::GL_Transform(glm::vec3 location,glm::vec3 rotation,glm::vec3 scale){
	_location=location;
	_scale=scale;
	_rotation=GLS::GL_Transform::normalizeAngles(rotation);
}
GLS::GL_Transform::~GL_Transform(){

}
glm::vec3 GLS::GL_Transform::getLocation()const{
	return _location;
}
glm::vec3 GLS::GL_Transform::getRotation()const{
	return _rotation;
}
glm::vec3 GLS::GL_Transform::getScale()const{
	return _scale;
}
void GLS::GL_Transform::move(const glm::vec3&delta){
	_location+=delta;
}
void GLS::GL_Transform::rotate(const glm::vec3&delta){
	_rotation=GLS::GL_Transform::normalizeAngles(_rotation+delta);
}
void GLS::GL_Transform::scaleBy(const glm::vec3&delta){
	_scale*=delta;
}
void GLS::GL_Transform::setLocation(const glm::vec3&location){
	_location=location;
}
void GLS::GL_Transform::setRotation(const glm::vec3&rotation){
	_rotation=GLS::GL_Transform::normalizeAngles(rotation);
}
void GLS::GL_Transform::setScale(const glm::vec3&scale){
	_scale=scale;
}
void GLS::GL_Transform::reset(){
	_location=glm::vec3(0.0f);
	_rotation=glm::vec3(0.0f);
	_scale=glm::vec3(1.0f);
}
