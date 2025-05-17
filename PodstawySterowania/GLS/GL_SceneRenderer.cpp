#include "GL_SceneRenderer.h"
#include "GL_Shape.h"
#include "GL_Mesh.h"
#include "GL_Shader.h"
#include "GL_GameObject.h"

GLS::GL_SceneRenderer::GL_SceneRenderer(glm::mat4 projection){
	_projection=projection;
}
GLS::GL_SceneRenderer::~GL_SceneRenderer(){

}
glm::mat4 GLS::GL_SceneRenderer::getProjection()const{
	return _projection;
}
void GLS::GL_SceneRenderer::setProjectionMatrix(glm::mat4 projection){
	_projection=projection;
}
void GLS::GL_SceneRenderer::renderObject(const GLS::GL_GameObject&gameObject)const{
	const GLS::GL_Mesh*meshComponent=gameObject.getMeshComponent();
	if(meshComponent==nullptr)
		return;
	if(!meshComponent->shouldRender())
		return;
	const GL_Shader*shaderComponent=gameObject.getShaderComponent();
	if(shaderComponent==nullptr)
		return;

	glm::mat4 model=glm::mat4(1.0f);

	glm::vec3 gameObjectLocation=gameObject.getLocation();
	glm::vec3 gameObjectRotation=gameObject.getRotation();
	glm::vec3 gameObjectScale=gameObject.getScale();

	glm::vec3 meshLocation=meshComponent->getLocalLocation();
	glm::vec3 meshRotation=meshComponent->getLocalRotation();
	glm::vec3 meshScale=meshComponent->getLocalScale();

	model=glm::translate(model,gameObjectLocation)*glm::rotate(model,glm::radians(gameObjectRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,gameObjectScale)*glm::translate(model,meshLocation)*glm::rotate(model,glm::radians(meshRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,meshScale);

	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(_projection));
	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"model"),1,GL_FALSE,glm::value_ptr(model));

	const GLS::GL_Shape*geometryMesh=meshComponent->getGeometry();

	const GLS::GL_Triangle*triangle=dynamic_cast<const GLS::GL_Triangle*>(geometryMesh);
	if(triangle){
		glUseProgram(shaderComponent->getShaderID());
		glBindVertexArray(triangle->getVAO());
		glDrawArrays(meshComponent->getRenderMode(),0,3);
		return;
	}
	const GLS::GL_Polygon*polygon=dynamic_cast<const GLS::GL_Polygon*>(geometryMesh);
	if(polygon){
		glUseProgram(shaderComponent->getShaderID());
		glBindVertexArray(polygon->getVAO());
		glDrawElements(meshComponent->getRenderMode(),polygon->getIndicesN(),GL_UNSIGNED_INT,0);
		return;
	}
}
void GLS::GL_SceneRenderer::renderScene(const std::vector<GLS::GL_GameObject*>& sceneObjects)const{
	for(auto it=sceneObjects.begin();it!=sceneObjects.end();++it){
		if((*it)->shouldRender())
			this->renderObject(*(*it));
	}
}
