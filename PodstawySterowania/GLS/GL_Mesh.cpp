#include "GL_Mesh.h"
#include "GL_GeometryManager.h"

namespace GLS{
    extern GL_GeometryManager GL_geometryManager;
}

GLS::GL_Mesh::GL_Mesh(std::string meshType,glm::vec3 location, glm::vec3 rotation,glm::vec3 scale){
	_meshGeometry=GLS::GL_geometryManager.getGeometryByName(meshType);
	_localTransform.setLocation(location);
	_localTransform.setRotation(rotation);
	_localTransform.setScale(scale);
	_renderEnable=GL_TRUE;
	_renderMode=GL_TRIANGLES;
	_color=glm::vec4(1.0f,0.0f,0.0f,1.0f);
}
GLS::GL_Mesh::GL_Mesh(GLuint vertN,glm::vec3 location, glm::vec3 rotation,glm::vec3 scale){
	_meshGeometry=GLS::GL_geometryManager.getGeometryByVertCount(vertN);
	_localTransform.setLocation(location);
	_localTransform.setRotation(rotation);
	_localTransform.setScale(scale);
	_renderEnable=GL_TRUE;
	_renderMode=GL_TRIANGLES;
	_color=glm::vec4(1.0f,0.0f,0.0f,1.0f);
}
GLS::GL_Mesh::~GL_Mesh(){

}
glm::vec3 GLS::GL_Mesh::getLocalLocation()const{
	return _localTransform.getLocation();
}
glm::vec3 GLS::GL_Mesh::getLocalRotation()const{
	return _localTransform.getRotation();
}
glm::vec3 GLS::GL_Mesh::getLocalScale()const{
	return _localTransform.getScale();
}
void GLS::GL_Mesh::setLocalLocation(glm::vec3 location){
	_localTransform.setLocation(location);
}
void GLS::GL_Mesh::setLocalRotation(glm::vec3 rotation){
	_localTransform.setRotation(rotation);
}
void GLS::GL_Mesh::setLocalScale(glm::vec3 scale){
	_localTransform.setScale(scale);
}
const GLS::GL_Shape*GLS::GL_Mesh::getGeometry()const{
	return _meshGeometry;
}
void GLS::GL_Mesh::changeGeometry(std::string meshType){
	_meshGeometry=GLS::GL_geometryManager.getGeometryByName(meshType);
}
void GLS::GL_Mesh::changeGeometry(GLuint vertN){
	_meshGeometry=GLS::GL_geometryManager.getGeometryByVertCount(vertN);
}
GLboolean GLS::GL_Mesh::shouldRender()const{
	return _renderEnable;
}
void GLS::GL_Mesh::enableRender(){
	_renderEnable=GL_TRUE;
}
void GLS::GL_Mesh::disableRender(){
	_renderEnable=GL_FALSE;
}
GLenum GLS::GL_Mesh::getRenderMode()const{
	return _renderMode;
}
void GLS::GL_Mesh::setRenderMode(GLenum renderMode){
	switch(renderMode){
		case GL_POINTS:
		case GL_LINES:
		case GL_LINE_LOOP:
		case GL_TRIANGLES:
		case GL_TRIANGLE_STRIP:
		case GL_TRIANGLE_FAN:
			_renderMode=renderMode;
			return;
		default:
		std::string exceptionText="Invalid renderMode in GL_Mesh";
		throw std::runtime_error(exceptionText.c_str());
	}
}
glm::vec4 GLS::GL_Mesh::getColor()const{
	return _color;
}
void GLS::GL_Mesh::setColor(glm::vec4 color){
	_color=color;
}