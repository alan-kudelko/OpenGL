#include "GL_Script.h"

GLS::GL_Script::GL_Script(std::string scriptName,void*scriptPtr){
	_scriptName=scriptName;
	_scriptPtr=scriptPtr;
}
GLS::GL_Script::~GL_Script(){
	
}
void GLS::GL_Script::executeScript(){
	if(_scriptPtr!=nullptr){
		// ScriptInit script initialization
		// ScriptLoop main script loop
	}
}
void GLS::GL_Script::enableExecution(){
	_shouldExecute=GL_TRUE;
}
void GLS::GL_Script::disableExecution(){
	_shouldExecute=GL_FALSE;
}
GLboolean GLS::GL_Script::shouldExecute()const{
	return _shouldExecute;
}