#include "GL_SceneRenderer.h"
#include "GL_Shape.h"
#include "GL_Shader.h"
#include "GL_GameObject.h"

GLS::GL_SceneRenderer::GL_SceneRenderer(glm::mat4 projection){
	_projection=projection;
}
GLS::GL_SceneRenderer::~GL_SceneRenderer(){

}
glm::mat4 GLS::GL_SceneRenderer::getProjectionMatrix()const{
	return _projection;
}
void GLS::GL_SceneRenderer::setProjectionMatrix(glm::mat4 projection){
	_projection=projection;
}
void GLS::GL_SceneRenderer::renderObject(const GLS::GL_GameObject&gameObject)const{
	const GL_Component*shapeComponent=gameObject.getShapeComponent();
	const GL_Shader*shaderComponent=gameObject.getShaderComponent();

	if(shapeComponent==nullptr)
		return;
	if(shaderComponent==nullptr)
		return;
	// Create some sort of debugging and logging

	glm::mat4 model=glm::mat4(1.0f); //basic model matrix

	glm::vec3 gameObjectLocation=gameObject.getGameObjectLocation();
	glm::vec3 gameObjectRotation=gameObject.getGameObjectRotation();

	glm::vec3 shapeComponentLocation=gameObject.getShapeComponentLocation();
	glm::vec3 shapeComponentRotation=gameObject.getShapeComponentRotation();
	glm::vec3 shapeComponentScale=gameObject.getShapeComponentSize();

	model=glm::translate(model,gameObjectLocation)*glm::rotate(model,glm::radians(gameObjectRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::translate(model,shapeComponentLocation)*glm::rotate(model,glm::radians(shapeComponentRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,shapeComponentScale);

	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(_projection));
	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"model"),1,GL_FALSE,glm::value_ptr(model));

	if(dynamic_cast<const GLS::GL_Triangle*>(shapeComponent)){
		const GLS::GL_Triangle*shape=dynamic_cast<const GLS::GL_Triangle*>(shapeComponent);

		glUseProgram(shaderComponent->getShaderID());
		glBindVertexArray(shape->getVAO());
		glDrawArrays(GL_TRIANGLES,0,3);
	}
	if(dynamic_cast<const GLS::GL_Polygon*>(shapeComponent)){
		const GLS::GL_Polygon*shape=dynamic_cast<const GLS::GL_Polygon*>(shapeComponent);

		glUseProgram(shaderComponent->getShaderID());
		glBindVertexArray(shape->getVAO());
		glDrawElements(GL_TRIANGLES,shape->getIndicesN(),GL_UNSIGNED_INT,0);
	}
}
void GLS::GL_SceneRenderer::renderScene(const std::vector<GLS::GL_GameObject*>& sceneObjects)const{
	for(auto it=sceneObjects.begin();it!=sceneObjects.end();++it){
		this->renderObject(*(*it));
	}
}
