#include "GL_SceneRenderer.h"
#include "GL_Shape.h"
#include "GL_Mesh.h"
#include "GL_Shader.h"
#include "GL_GameObject.h"
#include "GL_Collider.h"


void GLS::GL_SceneRenderer::renderCollider(GLS::GL_GameObject& gameObject){
    GLS::GL_Collider* colliderComponent=gameObject.getColliderComponent();
    if(!colliderComponent) return;

    const GL_Shader* shaderComponent=gameObject.getShaderComponent();
    if(!shaderComponent) return;

    glm::vec2 goPos=gameObject.getLocation();
    glm::vec2 goScale=gameObject.getScale();
    glm::vec2 colPos=colliderComponent->getLocalLocation();
    glm::vec2 colScale=colliderComponent->getLocalScale();
    
    GLfloat vertices[]={
        0.5f,    0.5f,
        0.5f,   -0.5f,
        -0.5f,  -0.5f,
        -0.5f,   0.5f
    };

    GLuint indices[]={
        0, 1, 2, 3, 0
    };
    GLuint VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

	glm::mat4 model=glm::mat4(1.0f);

	glm::vec2 gameObjectLocation=gameObject.getLocation();
	glm::vec3 gameObjectRotation=gameObject.getRotation();
	glm::vec2 gameObjectScale=gameObject.getScale();

	glm::vec2 colliderLocation=colliderComponent->getLocalLocation()/gameObjectScale;
	glm::vec3 colliderRotation=colliderComponent->getLocalRotation();
	glm::vec2 colliderScale=colliderComponent->getLocalScale();

	glm::mat3 boundingBoxRotation=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(gameObjectRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

	auto mat3abs=[](glm::mat3& m){
		for(GLuint i=0;i < 3;i++)
			m[i]=glm::abs(m[i]);
		return m;
	};

	gameObjectScale=mat3abs(boundingBoxRotation) *glm::vec3(gameObjectScale,1.0f);

	model=glm::translate(model,glm::vec3(gameObjectLocation,0.0f))* glm::scale(model,glm::vec3(gameObjectScale,1.0f)) * glm::translate(model,glm::vec3(colliderLocation,0.0f));

    glUseProgram(shaderComponent->getShaderID());
    glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(_projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"model"),1,GL_FALSE,glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_LINE_STRIP,5,GL_UNSIGNED_INT,0);

    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
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
void GLS::GL_SceneRenderer::renderScene(std::vector<GLS::GL_GameObject*>& sceneObjects){
	for(auto it=sceneObjects.begin();it!=sceneObjects.end();++it){
		if((*it)->shouldRender())
			this->renderObject(*(*it));
		if(_renderCollider)
			this->renderCollider(*(*it));
	}
}
