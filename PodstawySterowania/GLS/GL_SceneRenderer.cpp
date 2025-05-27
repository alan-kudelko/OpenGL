#include "GL_SceneRenderer.h"
#include "GL_Shape.h"
#include "GL_Mesh.h"
#include "GL_Shader.h"
#include "GL_GameObject.h"
#include "GL_Collider.h"
#include "GL_ResourceManager.h"

namespace GLS{
	extern GL_ResourceManager GL_resourceManager;
}

void GLS::GL_SceneRenderer::renderCollider(GLS::GL_GameObject& gameObject){
    GLS::GL_Collider* colliderComponent=gameObject.getColliderComponent();
    if(!colliderComponent) return;

    const GL_Shader* shaderComponent=GLS::GL_resourceManager.getShaderByName("boundingBoxShader");
    if(!shaderComponent) return;
    
	glm::vec2 vertices[4]{};

	colliderComponent->getAABBvertices(vertices);

	GLuint vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glUseProgram(shaderComponent->getShaderID());
	glUniform4fv(glGetUniformLocation(shaderComponent->getShaderID(),"u_color"),1,glm::value_ptr(colliderComponent->getRenderColor()));
	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(_projection));
	glUniform2fv(glGetUniformLocation(shaderComponent->getShaderID(),"u_AABB"),4,&vertices[0].x);

	glDrawArrays(GL_LINE_LOOP,0,4);

	glDeleteVertexArrays(1,&vao);
}
GLS::GL_SceneRenderer::GL_SceneRenderer(glm::mat4 projection){
	_projection=projection;
	_renderCollider=GL_TRUE;
}
GLS::GL_SceneRenderer::~GL_SceneRenderer(){

}
glm::mat4 GLS::GL_SceneRenderer::getProjection()const{
	return _projection;
}
void GLS::GL_SceneRenderer::setProjectionMatrix(glm::mat4 projection){
	_projection=projection;
}
void GLS::GL_SceneRenderer::renderObject(GLS::GL_GameObject&gameObject){
	const GLS::GL_Mesh*meshComponent=gameObject.getMeshComponent();
	if(meshComponent==nullptr)
		return;
	if(!meshComponent->shouldRender())
		return;
	const GL_Shader*shaderComponent=gameObject.getShaderComponent();
	if(shaderComponent==nullptr)
		return;

	glm::mat4 model=glm::mat4(1.0f);

	glm::vec2 gameObjectLocation=gameObject.getLocation();
	glm::vec3 gameObjectRotation=gameObject.getRotation();
	glm::vec2 gameObjectScale=gameObject.getScale();

	glm::vec2 meshLocation=meshComponent->getLocalLocation();
	glm::vec3 meshRotation=meshComponent->getLocalRotation();
	glm::vec2 meshScale=meshComponent->getLocalScale();

	model=glm::translate(model,glm::vec3(gameObjectLocation,0.0f))*glm::rotate(model,glm::radians(gameObjectRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,glm::vec3(gameObjectScale,1.0f))*glm::translate(model,glm::vec3(meshLocation,0.0f))*glm::rotate(model,glm::radians(meshRotation.z),glm::vec3(0.0f,0.0f,1.0f))*glm::scale(model,glm::vec3(meshScale,1.0f));

	glUseProgram(shaderComponent->getShaderID());
	glUniform4fv(glGetUniformLocation(shaderComponent->getShaderID(),"u_color"),1,glm::value_ptr(meshComponent->getColor()));
	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(_projection));
	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"model"),1,GL_FALSE,glm::value_ptr(model));

	const GLS::GL_Shape*geometryMesh=meshComponent->getGeometry();

	const GLS::GL_Triangle*triangle=dynamic_cast<const GLS::GL_Triangle*>(geometryMesh);
	if(triangle){
		glBindVertexArray(triangle->getVAO());
		glDrawArrays(meshComponent->getRenderMode(),0,3);
		return;
	}
	const GLS::GL_Polygon*polygon=dynamic_cast<const GLS::GL_Polygon*>(geometryMesh);
	if(polygon){
		glBindVertexArray(polygon->getVAO());
		glDrawElements(meshComponent->getRenderMode(),polygon->getIndicesN(),GL_UNSIGNED_INT,0);
		return;
	}
}
void GLS::GL_SceneRenderer::renderScene(std::vector<GLS::GL_GameObject*>& sceneObjects){
	for(auto it=sceneObjects.begin();it!=sceneObjects.end();++it){
		if((*it)->shouldRender())
			this->renderObject(*(*it));
		if(_renderCollider)
			this->renderCollider(*(*it));
	}
}
