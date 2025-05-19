#include "GL_SceneRenderer.h"
#include "GL_Shape.h"
#include "GL_Mesh.h"
#include "GL_Shader.h"
#include "GL_GameObject.h"
#include "GL_Collider.h"


void GLS::GL_SceneRenderer::renderCollider(GLS::GL_GameObject& gameObject){
	GLS::GL_Collider*colliderComponent=gameObject.getColliderComponent();
	GLS::GL_Mesh*meshComponent=gameObject.getMeshComponent();

	if(colliderComponent==nullptr)
		return;
	const GL_Shader*shaderComponent=gameObject.getShaderComponent();
	if(shaderComponent==nullptr)
		return;

	glm::vec3 obj1GoLocation=gameObject.getLocation();
	glm::vec3 obj1GoRotation=gameObject.getRotation();
	glm::vec3 obj1GoScale=gameObject.getScale();

	glm::vec3 obj1ColLocation=colliderComponent->getLocalLocation();
	glm::vec3 obj1ColRotation=colliderComponent->getLocalRotation();
	glm::vec3 obj1ColScale=colliderComponent->getLocalScale();

	auto mat3abs=[](glm::mat3& m){
		for(GLuint i=0;i < 3;i++)
			m[i]=glm::abs(m[i]);
		return m;
	};

	auto mat4abs=[](glm::mat4 m){
		for(GLuint i=0;i < 4;i++)
			m[i]=glm::abs(m[i]);
		return m;
	};
	auto getCords=[](glm::mat4 m)->glm::vec3{
		return glm::vec3(m[3][0],m[3][1],m[3][2]);
	};

	// RU RL LU LL
	glm::mat3 boundingBoxRotation=glm::mat3(glm::rotate(glm::mat4(1.0f),glm::radians(obj1GoRotation.z),glm::vec3(0.0f,0.0f,1.0f)));

	obj1ColScale=mat3abs(boundingBoxRotation) * obj1ColScale;

	glm::vec3 obj1ColRU=obj1GoLocation + obj1ColScale / 2.0f;
	glm::vec3 obj1ColLL=obj1GoLocation - obj1ColScale / 2.0f;
	glm::vec3 obj1ColRL=obj1ColRU-glm::vec3(0.0f,obj1ColScale.y,0.0f);
	glm::vec3 obj1ColLU=obj1ColLL+glm::vec3(0.0f,obj1ColScale.y,0.0f);

	glm::mat4 model=glm::mat4(1.0f);

	GLfloat obj1Col[12]{obj1ColRU.x,obj1ColRU.y,obj1ColRU.z,
						obj1ColRL.x,obj1ColRL.y,obj1ColRL.z,
						obj1ColLL.x,obj1ColLL.y,obj1ColLL.z,
						obj1ColLU.x,obj1ColLU.y,obj1ColLU.z};

	// Fix this
	GLuint indices[6]={0,1,2,3,0,0};
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,12 * sizeof(GLfloat),obj1Col,GL_DYNAMIC_DRAW);

	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint) * 6,indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(void*)0);
	glEnableVertexAttribArray(0);

	model=(glm::translate(model,obj1GoLocation) *
		glm::scale(model,obj1GoScale));

	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"projection"),1,GL_FALSE,glm::value_ptr(_projection));
	glUniformMatrix4fv(glGetUniformLocation(shaderComponent->getShaderID(),"model"),1,GL_FALSE,glm::value_ptr(model));

	const GLS::GL_Polygon* polygon=dynamic_cast<const GLS::GL_Polygon*>(meshComponent->getGeometry());
	if(polygon){
		glUseProgram(shaderComponent->getShaderID());
		glBindVertexArray(VAO);
		glDrawElements(GL_LINE_LOOP,EBO,GL_UNSIGNED_INT,0);
		return;
	}
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
void GLS::GL_SceneRenderer::renderScene(std::vector<GLS::GL_GameObject*>& sceneObjects){
	for(auto it=sceneObjects.begin();it!=sceneObjects.end();++it){
		if((*it)->shouldRender())
			this->renderObject(*(*it));
		//if(_renderCollider)
			//this->renderCollider(*(*it));
	}
}
