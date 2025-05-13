#include "GL_SceneManager.h"

GLS::GL_SceneManager::GL_SceneManager(){

}
GLS::GL_SceneManager::~GL_SceneManager(){
	clearScene();
}
void GLS::GL_SceneManager::addNewGameObject(GLS::GL_GameObject*gameObject){
	_sceneObjects.push_back(gameObject);
}
const std::vector<GLS::GL_GameObject*>&GLS::GL_SceneManager::getSceneObjects()const{
	return _sceneObjects;
}
GLS::GL_GameObject*GLS::GL_SceneManager::getSceneObject(GLuint it){
	return _sceneObjects[it];
}
GLuint GLS::GL_SceneManager::getSceneObjectNumber()const{
	return _sceneObjects.size();
}
void GLS::GL_SceneManager::clearScene(){
	_sceneObjects.clear();
}
void GLS::GL_SceneManager::updateScene(){
    for(auto it=_sceneObjects.begin();it!=_sceneObjects.end();){
        if((*it)->shouldDestroy()){
			it=_sceneObjects.erase(it);
        }
		else
			++it;
    }
}
