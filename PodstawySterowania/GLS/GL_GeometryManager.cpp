#include "GL_GeometryManager.h"
#include "GL_Shape.h"

namespace GLS{
	GL_GeometryManager GL_geometryManager;
}

auto GLS::GL_GeometryManager::_findGeometryByVertCount(GLuint vertN)const{
	for(auto it=_shapeRecords.begin();it!=_shapeRecords.end();++it){
		if((*it).vertN==vertN)
		return it;
	}
	return _shapeRecords.end();
}
GLS::GL_GeometryManager::GL_GeometryManager(){

}
GLS::GL_GeometryManager::~GL_GeometryManager(){
    for(auto& shapeRecord:_shapeRecords){
        delete shapeRecord.shape;
    }
}
GLS::GL_Shape*GLS::GL_GeometryManager::getGeometryByName(std::string meshType){
	if(meshType=="Triangle"){
		return this->getGeometryByVertCount(3);
	}
	if(meshType=="Rectangle"){
		return this->getGeometryByVertCount(4);
	}
	else{
		std::string exceptionText = "GL_GeometryManager trying to return undefined geometry name: "+meshType;
		throw std::runtime_error(exceptionText.c_str());
	}
}
GLS::GL_Shape*GLS::GL_GeometryManager::getGeometryByVertCount(GLuint vertN){
	auto it=this->_findGeometryByVertCount(vertN);
	if(it==_shapeRecords.end()){
        GLS::GL_Shape*shape;
		if(vertN<3){
			std::string exceptionText="GL_GeometryManager cannot create shape with less than 3 vertices yet";
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
