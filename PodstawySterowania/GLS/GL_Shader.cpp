#include "GL_Shader.h"

namespace GLS{
    const char*GL_SHADER_LOG_FILENAME="./Log/GL_Shader";
}

std::string GLS::GL_Shader::_loadShader(const char*shaderPath){
    std::stringstream shaderSourceCode;
    std::ifstream shaderFile;
    shaderFile.open(shaderPath);
	if(!shaderFile.is_open()){
		std::ofstream logFile;
		std::string logFileName(_getLogFilePath());
		logFile.open(logFileName.c_str(),std::ios_base::app);
        logFile<<"Error opening file: "<<shaderPath<<std::endl;
		logFile.close();
		_shaderStatus|=1;
		return std::string("");
	}
    shaderSourceCode<<shaderFile.rdbuf();
    shaderFile.close();
    return shaderSourceCode.str();
}
GLuint GLS::GL_Shader::_compileShader(const char*shaderPath,GLenum shaderType){
    std::string shaderSourceCode=_loadShader(shaderPath);
	if(shaderSourceCode=="")
		return 0;
    const char*source=shaderSourceCode.c_str();

    GLuint shader=glCreateShader(shaderType);
	GLint status;
    glShaderSource(shader,1,&source,nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
    if(!status){
        char log[512]{};
		std::ofstream logFile;
        std::string logFileName(_getLogFilePath());
		logFile.open(logFileName.c_str(),std::ios_base::app);
        glGetShaderInfoLog(shader,512,nullptr,log);

		if(shaderType==GL_VERTEX_SHADER){
			_shaderStatus|=8;
		}
		if(shaderType==GL_FRAGMENT_SHADER){
			_shaderStatus|=4;
		}
		logFile<<"Error in: "<<shaderPath<<' ';
		logFile<<log<<std::endl;

		logFile.close();

        return 0;
    }
    return shader;
}
std::string GLS::GL_Shader::_getCurrentSystemTime()const{
	std::time_t t=std::time(0);
	std::tm*currentTime=std::localtime(&t);
	std::string currentTimeStr=std::to_string(currentTime->tm_year+1900);
	currentTimeStr+='_'+((currentTime->tm_mon+1>9)?std::to_string(currentTime->tm_mon+1):('0'+std::to_string(currentTime->tm_mon+1)));
	currentTimeStr+='_'+((currentTime->tm_mday>9)?std::to_string(currentTime->tm_mday):('0'+std::to_string(currentTime->tm_mday)));
    currentTimeStr+='_'+((currentTime->tm_hour>9)?std::to_string(currentTime->tm_hour):('0'+std::to_string(currentTime->tm_hour)));
    currentTimeStr+='_'+((currentTime->tm_min>9)?std::to_string(currentTime->tm_min):('0'+std::to_string(currentTime->tm_min)));
    currentTimeStr+='_'+((currentTime->tm_sec>9)?std::to_string(currentTime->tm_sec):('0'+std::to_string(currentTime->tm_sec)));
	return currentTimeStr;
}
std::string GLS::GL_Shader::_getLogFilePath()const{
	std::string logFileName=GLS::GL_SHADER_LOG_FILENAME;
	logFileName+='_'+_getCurrentSystemTime();
	logFileName+=".log";

	return logFileName;
}
GLuint GLS::GL_Shader::_createShaderProgram(const char*vertexShaderPath,const char*fragmentShaderPath){
    GLuint vertexShader=_compileShader(vertexShaderPath,GL_VERTEX_SHADER);
    GLuint fragmentShader=_compileShader(fragmentShaderPath,GL_FRAGMENT_SHADER);
	GLint status;
    _shaderN=glCreateProgram();
    glAttachShader(_shaderN,vertexShader);
    glAttachShader(_shaderN,fragmentShader);
    glLinkProgram(_shaderN);

    glGetProgramiv(_shaderN,GL_LINK_STATUS,&status);
    if(!status){
        char log[512]{};
		std::ofstream logFile;
        std::string logFileName(_getLogFilePath());
		logFile.open(logFileName.c_str(),std::ios_base::app);
        glGetProgramInfoLog(_shaderN,512,nullptr,log);
		logFile<<"Error in: "<<' ';
		logFile<<log<<std::endl;
		logFile.close();

		_shaderStatus|=2;
        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return _shaderN;
}
GLS::GL_Shader::GL_Shader(const char*vertexShaderPath,const char*fragmentShaderPath){
	_shaderStatus=0;
	_shaderN=_createShaderProgram(vertexShaderPath,fragmentShaderPath);
	_vertexShaderPath=vertexShaderPath;
	_fragmentShaderPath=fragmentShaderPath;
}
GLS::GL_Shader::GL_Shader(std::string vertexShaderPath,std::string fragmentShaderPath){
	_shaderStatus=0;
	_shaderN=_createShaderProgram(vertexShaderPath.c_str(),fragmentShaderPath.c_str());
	_vertexShaderPath=vertexShaderPath;
	_fragmentShaderPath=fragmentShaderPath;
}
GLS::GL_Shader::~GL_Shader(){
	glDeleteProgram(_shaderN);
}
GLuint GLS::GL_Shader::getShaderID()const{
	return _shaderN;
}
GLuint GLS::GL_Shader::getShaderStatus()const{
	return _shaderStatus;
}
