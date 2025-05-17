#include "GL_SceneManager.h"
#include "GL_GameObject.h"

GLS::GL_SceneManager::GL_SceneManager(){

}
GLS::GL_SceneManager::~GL_SceneManager(){
	clearScene();
}
void GLS::GL_SceneManager::addNewGameObject(GLS::GL_GameObject*gameObject){
	_sceneObjects.push_back(gameObject);
}
const std::vector<GLS::GL_GameObject*>&GLS::GL_SceneManager::getSceneObjectsConst()const{
	return _sceneObjects;
}
std::vector<GLS::GL_GameObject*>&GLS::GL_SceneManager::getSceneObjectsMutable(){
	return _sceneObjects;
}
const GLS::GL_GameObject&GLS::GL_SceneManager::getSceneObjectConst(GLuint index)const{
	return *_sceneObjects[index];
}
GLS::GL_GameObject&GLS::GL_SceneManager::getSceneObjectMutable(GLuint index){
	return *_sceneObjects[index];
}
GLuint GLS::GL_SceneManager::getSceneObjectNumber()const{
	return _sceneObjects.size();
}
void GLS::GL_SceneManager::clearScene(){
	_sceneObjects.clear();
}
void GLS::GL_SceneManager::updateScene(GLuint offset){
    for(auto it=_sceneObjects.begin()+offset;it!=_sceneObjects.end();){
        if((*it)->shouldDestroy()){
			it=_sceneObjects.erase(it);
        }
		else
			++it;
    }
}
