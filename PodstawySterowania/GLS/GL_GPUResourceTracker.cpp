#include "GL_GPUResourceTracker.h"

GLS::GPUResourceTracker::GPUResourceTracker(){
	_VAO_N=0;
	_VBO_N=0;
	_Shader_N=0;

	_VAO_N_Capacity=100;
	_VBO_N_Capacity=100;
	_Shader_N_Capacity=100;

	_VAO_List=new GLboolean[_VAO_N_Capacity]{};
	_VBO_List=new GLboolean[_VAO_N_Capacity]{};
	_Shader_List=new GLboolean[_VAO_N_Capacity]{};
}
GLS::GPUResourceTracker::~GPUResourceTracker(){
	delete[]_VAO_List;
	delete[]_VBO_List;
	delete[]_Shader_List;
}

GLuint GLS::GPUResourceTracker::getFirstEmptyVAO()const{
	GLuint i=0;
	for(;i<_VAO_N_Capacity;i++){
		if(!_VAO_List[i])
			break;
	}
	return i+1;
}
GLuint GLS::GPUResourceTracker::getFirstEmptyVBO()const{
	GLuint i=0;
	for(;i<_VBO_N_Capacity;i++){
		if(!_VBO_List[i])
			break;
	}
	return i+1;
}
GLuint GLS::GPUResourceTracker::getFirstEmptyShader()const{
	GLuint i=0;
	for(;i<_Shader_N_Capacity;i++){
		if(!_Shader_List[i])
			break;
	}
	return i+1;
}

GLuint GLS::GPUResourceTracker::addFirstEmptyVAO(){
	if(_VAO_N+1>_VAO_N_Capacity){
		GLuint _VAO_N_Capacity_Temp=_VAO_N_Capacity*2;
		GLboolean*_VAO_List_Temp=new GLboolean[_VAO_N_Capacity_Temp]{};
		GLuint i=0;
		for(;i<_VAO_N_Capacity;i++){
			_VAO_List_Temp[i]=_VAO_List[i];
		}

		delete[]_VAO_List;
		_VAO_List=_VAO_List_Temp;

		_VAO_N_Capacity=_VAO_N_Capacity_Temp;
	}
	GLuint _first_Empty_VAO=this->getFirstEmptyVAO();
	_VAO_List[_first_Empty_VAO-1]=GL_TRUE;
	_VAO_N++;

	return _VAO_N;
}
GLuint GLS::GPUResourceTracker::addFirstEmptyVBO(){
	if(_VBO_N+1>_VBO_N_Capacity){
		GLuint _VBO_N_Capacity_Temp=_VBO_N_Capacity*2;
		GLboolean*_VBO_List_Temp=new GLboolean[_VBO_N_Capacity_Temp]{};
		GLuint i=0;
		for(;i<_VBO_N_Capacity;i++){
			_VBO_List_Temp[i]=_VBO_List[i];
		}

		delete[]_VBO_List;
		_VBO_List=_VBO_List_Temp;

		_VBO_N_Capacity=_VBO_N_Capacity_Temp;
	}
	GLuint _first_Empty_VBO=this->getFirstEmptyVBO();
	_VBO_List[_first_Empty_VBO-1]=GL_TRUE;
	_VBO_N++;

	return _VBO_N;
}
GLuint GLS::GPUResourceTracker::addFirstEmptyShader(){
	if(_Shader_N=1>_Shader_N_Capacity){
		GLuint _Shader_N_Capacity_Temp=_Shader_N_Capacity*2;
		GLboolean*_Shader_List_Temp=new GLboolean[_Shader_N_Capacity_Temp]{};
		GLuint i=0;
		for(;i<_Shader_N_Capacity;i++){
			_Shader_List_Temp[i]=_Shader_List[i];
		}

		delete[]_Shader_List;
		_Shader_List=_Shader_List_Temp;

		_Shader_N_Capacity=_Shader_N_Capacity_Temp;
	}
	GLuint _first_Empty_Shader=this->getFirstEmptyShader();
	_Shader_List[_first_Empty_Shader-1]=GL_TRUE;
	_Shader_N++;

	return _Shader_N;
}

GLuint GLS::GPUResourceTracker::getNumberVAO()const{
	return _VAO_N;
}
GLuint GLS::GPUResourceTracker::getNumberVBO()const{
	return _VBO_N;
}
GLuint GLS::GPUResourceTracker::getNumberShader()const{
	return _Shader_N;
}

GLuint GLS::GPUResourceTracker::removeVAO(GLuint _VAO){
	GLuint i=0;
	for(;i<_VAO_N_Capacity;i++){
		if(i+1==_VAO){
			_VAO_List[i]=GL_FALSE;
			break;
		}
	}
	if(_VAO_N-1==0){
		_VAO_N_Capacity=100;
		delete[]_VAO_List;
		_VAO_List=new GLboolean[_VAO_N_Capacity]{};
	}

	return --_VAO_N;
}
GLuint GLS::GPUResourceTracker::removeVBO(GLuint _VBO){
	GLuint i=0;
	for(;i<_VBO_N_Capacity;i++){
		if(i+1==_VBO){
			_VBO_List[i]=GL_FALSE;
			break;
		}
	}
	if(_VBO_N-1==0){
		_VBO_N_Capacity=100;
		delete[]_VBO_List;
		_VBO_List=new GLboolean[_VBO_N_Capacity]{};
	}
	return --_VBO_N;
}
GLuint GLS::GPUResourceTracker::removeShader(GLuint _Shader){
	GLuint i=0;
	for(;i<_Shader_N_Capacity;i++){
		if(i+1==_Shader){
			_Shader_List[i]=GL_FALSE;
			break;
		}
	}
	if(_Shader_N-1==0){
		_Shader_N_Capacity=100;
		delete[]_Shader_List;
		_Shader_List=new GLboolean[_Shader_N_Capacity]{};
	}
	return --_Shader_N;
}
