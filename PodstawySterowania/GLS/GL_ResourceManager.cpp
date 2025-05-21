#include "GL_ResourceManager.h"
#include "GL_Shape.h"
#include "GL_Shader.h"

namespace GLS{
	GL_ResourceManager GL_resourceManager;
}

auto GLS::GL_ResourceManager::_findGeometryByVertCount(GLuint vertN)const{
	for(auto it=_shapeRecords.begin();it!=_shapeRecords.end();++it){
		if((*it).vertN==vertN)
			return it;
	}
	return _shapeRecords.end();
}
auto GLS::GL_ResourceManager::_findShaderByName(std::string shaderName)const{
	for(auto it=_shaderRecords.begin();it!=_shaderRecords.end();++it){
		if((*it).shaderName==shaderName)
			return it;
	}
	return _shaderRecords.end();
}
GLS::GL_ResourceManager::GL_ResourceManager(){

}
GLS::GL_ResourceManager::~GL_ResourceManager(){
    for(auto& shapeRecord:_shapeRecords)
        delete shapeRecord.shape;
	for(auto& shaderRecord:_shaderRecords)
		delete shaderRecord.shader;
}
GLS::GL_Shape*GLS::GL_ResourceManager::getGeometryByName(std::string meshType){
	if(meshType=="Triangle"){
		return this->getGeometryByVertCount(3);
	}
	if(meshType=="Rectangle"){
		return this->getGeometryByVertCount(4);
	}
	else{
		std::string exceptionText = "GL_ResourceManager trying to return undefined geometry name: "+meshType;
		throw std::runtime_error(exceptionText.c_str());
	}
}
GLS::GL_Shape*GLS::GL_ResourceManager::getGeometryByVertCount(GLuint vertN){
	auto it=this->_findGeometryByVertCount(vertN);
	if(it==_shapeRecords.end()){
        GLS::GL_Shape*shape;
		if(vertN<3){
			std::string exceptionText="GL_ResourceManager cannot create shape with less than 3 vertices yet";
			throw std::runtime_error(exceptionText.c_str());
		}
		if(vertN==3)
			shape=new GLS::GL_Triangle;
		if(vertN>3)
			shape=new GLS::GL_Polygon(vertN);
		GL_ShapeEntry shapeEntry{shape,vertN};
		_shapeRecords.push_back(shapeEntry);
		it=_shapeRecords.end()-1;
	}
	return (*it).shape;
}
void GLS::GL_ResourceManager::createShader(std::string shaderName,std::string vertexShaderPath,std::string fragmentShaderPath){
	if(this->_findShaderByName(shaderName)!=_shaderRecords.end()){
		std::string exceptionText="GL_ResourceManager cannot create shader with the same name: "+shaderName;
		throw std::runtime_error(exceptionText.c_str());
	}
	GLS::GL_Shader*shader=new GLS::GL_Shader(vertexShaderPath,fragmentShaderPath);
	if(shader==nullptr){
		std::string exceptionText="GL_ResourceManager cannot create shader, check log file";
		throw std::runtime_error(exceptionText.c_str());
	}
	GL_ShaderEntry shaderEntry{shader,shaderName,vertexShaderPath,fragmentShaderPath};
	_shaderRecords.push_back(shaderEntry);
}
GLS::GL_Shader*GLS::GL_ResourceManager::getShaderByName(std::string shaderName)const{
	auto it=this->_findShaderByName(shaderName);
	if(it==_shaderRecords.end()){
		std::string exceptionText="GL_ResourceManager canno find shader: "+shaderName;
		throw std::runtime_error(exceptionText.c_str());
	}

	return (*it).shader;	
}