#include "GL_Collider.h"
#include "GL_Transform.h"

////////////////////////////////////////////////////////////////// GL_Collider
GLS::GL_Collider::GL_Collider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup){
	_localTransform.setLocation(location);
	_localTransform.setRotation(rotation);
	_localTransform.setScale(scale);
	_collisionGroup=collisionGroup;
	_collisionEnable=GL_TRUE;

	_renderColor=glm::vec4(1.0f,1.0f,1.0f,1.0f);
}
GLS::GL_Collider::~GL_Collider(){

}
GLuint GLS::GL_Collider::getCollisionGroup()const{
	return _collisionGroup;
}
GLS::GL_Transform GLS::GL_Collider::getLocalTransform()const{
	return _localTransform;
}
glm::vec2 GLS::GL_Collider::getLocalLocation()const{
	return _localTransform.getLocation();
}
glm::vec3 GLS::GL_Collider::getLocalRotation()const{
	return _localTransform.getRotation();
}
glm::vec2 GLS::GL_Collider::getLocalScale()const{
	return _localTransform.getScale();
}
void GLS::GL_Collider::setCollisionGroup(GLuint collisionGroup){
	_collisionGroup=collisionGroup;
}
void GLS::GL_Collider::setLocalLocation(glm::vec2 location){
	_localTransform.setLocation(location);
}
void GLS::GL_Collider::setLocalRotation(glm::vec3 rotation){
	_localTransform.setRotation(rotation);
}
void GLS::GL_Collider::setLocalScale(glm::vec2 scale){
	_localTransform.setScale(scale);
}
glm::vec4 GLS::GL_Collider::getRenderColor()const{
	return _renderColor;
}
void GLS::GL_Collider::setRenderColor(glm::vec4 color){
	_renderColor=color;
}
void GLS::GL_Collider::enableCollisions(){
	_collisionEnable=GL_TRUE;
}
void GLS::GL_Collider::disableCollisions(){
	_collisionEnable=GL_FALSE;
}
GLboolean GLS::GL_Collider::shouldCollide()const{
	return _collisionEnable;
}
void GLS::GL_Collider::getAABBvertices(glm::vec2* AABB)const{
	for(GLuint i=0;i<4;i++)
		AABB[i]=_AABBvertices[i];
}
void GLS::GL_Collider::setAABBvertices(glm::vec2* AABB){
	for(GLuint i=0;i<4;i++)
		_AABBvertices[i]=AABB[i];
}
void GLS::GL_Collider::setAABBvertices(std::vector<glm::vec2> AABB){
	for(GLuint i=0;i<4;i++)
		_AABBvertices[i]=AABB[i];
}
////////////////////////////////////////////////////////////////// GL_VertexCollider
GLS::GL_VertexCollider::GL_VertexCollider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale, GLuint collisionGroup):GLS::GL_Collider(location,rotation,scale,collisionGroup){
	_colliderVertices=nullptr;
	_colliderVertCount=0;
	_isConvex=GL_TRUE;
}
void GLS::GL_VertexCollider::getVertices(glm::vec2*vertices)const{
	for(GLuint i=0;i < 4;i++) {
		vertices[i]=_colliderVertices[i];
	}
}
GLuint GLS::GL_VertexCollider::getVertCount()const{
	return _colliderVertCount;
}
////////////////////////////////////////////////////////////////// GL_BoxCollider
GLS::GL_BoxCollider::GL_BoxCollider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup):GLS::GL_VertexCollider(location,rotation,scale,collisionGroup){
	_colliderVertices=new glm::vec2[4]{};
	_colliderVertCount=4;
	GLfloat angle=45.0f;
	GLfloat angleIncrement=90.0f;
	GLfloat radius=sqrt(2)/2;

	for(GLuint i=0;i < 4;i++,angle+=angleIncrement){
		_colliderVertices[i].x=std::sin(glm::radians(angle))*radius;
		_colliderVertices[i].y=std::cos(glm::radians(angle))*radius;
	}
}
GLS::GL_BoxCollider::~GL_BoxCollider(){
	delete[]_colliderVertices;
}
void GLS::GL_BoxCollider::setVertices(glm::vec2*vertices){
	for (GLuint i=0;i<4;i++){
		vertices[i]=_colliderVertices[i];
	}
}
////////////////////////////////////////////////////////////////// GL_MeshCollider
GLS::GL_MeshCollider::GL_MeshCollider(glm::vec2*vertices,GLuint vertCount,glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup):GLS::GL_VertexCollider(location,rotation,scale,collisionGroup){
	_colliderVertCount=vertCount;
	_colliderVertices=new glm::vec2[_colliderVertCount];
	_colliderVertices=vertices;
	// Note for future, this collider can be only created if there is GL_Mesh component present in GL_GameObject
}
GLS::GL_MeshCollider::~GL_MeshCollider(){
	// Do not delete geometry as it is managed by GL_Mesh
}
void GLS::GL_MeshCollider::setVertices(glm::vec2* vertices,GLuint vertCount){

}
////////////////////////////////////////////////////////////////// GL_SphereCollider
GLS::GL_SphereCollider::GL_SphereCollider(glm::vec2 location,glm::vec3 rotation,glm::vec2 scale,GLuint collisionGroup):GL_Collider(location,rotation,scale,collisionGroup){
	
}
GLS::GL_SphereCollider::~GL_SphereCollider(){

}