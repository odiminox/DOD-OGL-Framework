

#include "GLSLShader.h"
#include <iostream>


GLSLShader::GLSLShader(void)
{
	_totalShaders=0;
	_shaders[VERTEX_SHADER]=0;
	_shaders[FRAGMENT_SHADER]=0;
	_shaders[GEOMETRY_SHADER]=0;
	_shaders[COMPUTE_SHADER]=0;
	_attributeList.clear();
	_uniformLocationList.clear();
}

GLSLShader::~GLSLShader(void)
{
	_attributeList.clear();
	_uniformLocationList.clear();
}

void GLSLShader::LoadFromString(GLenum type, const string source) {
	GLuint shader = glCreateShader (type);

	const char * ptmp = source.c_str();
	glShaderSource (shader, 1, &ptmp, NULL);

	//check whether the shader loads fine
	GLint status;
	glCompileShader (shader);
	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog= new GLchar[infoLogLength];
		glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
		cout<<GFXCALL"Compile log: "<<infoLog<<endl;
		delete [] infoLog;
	}
	_shaders[_totalShaders++]=shader;
}


void GLSLShader::CreateAndLinkProgram() {
	_program = glCreateProgram ();
	if (_shaders[VERTEX_SHADER] != 0) {
		glAttachShader (_program, _shaders[VERTEX_SHADER]);
	}
	if (_shaders[FRAGMENT_SHADER] != 0) {
		glAttachShader (_program, _shaders[FRAGMENT_SHADER]);
	}
	if (_shaders[GEOMETRY_SHADER] != 0) {
		glAttachShader (_program, _shaders[GEOMETRY_SHADER]);
	}
	if(_shaders[COMPUTE_SHADER] != 0) {
		glAttachShader (_program, _shaders[COMPUTE_SHADER]);
	}

	//link and check whether the program links fine
	GLint status;
	glLinkProgram (_program);
	glGetProgramiv (_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;

		glGetProgramiv (_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog= new GLchar[infoLogLength];
		glGetProgramInfoLog (_program, infoLogLength, NULL, infoLog);
		cout<<GFXCALL"Link log: "<<infoLog<<endl;
		delete [] infoLog;
	}

	glDeleteShader(_shaders[VERTEX_SHADER]);
	glDeleteShader(_shaders[FRAGMENT_SHADER]);
	glDeleteShader(_shaders[GEOMETRY_SHADER]);
}



void GLSLShader::bind() {
	glUseProgram(_program);
}

void GLSLShader::unbind() {
	glUseProgram(0);
}

void GLSLShader::AddAttribute(const string attribute) {
	_attributeList[attribute]= glGetAttribLocation(_program, attribute.c_str());
}

//This has been modified from the IOS port so may contain some errors
void GLSLShader::loadAttribute(GLuint& inAttribName, std::string name)
{
	inAttribName  = glGetAttribLocation(_program, name.c_str());
	glEnableVertexAttribArray(inAttribName);

}

//An indexer that returns the location of the attribute
GLuint GLSLShader::operator [](const string attribute) {
	return _attributeList[attribute];
}

void GLSLShader::AddUniform(const string uniform) {
	_uniformLocationList[uniform] = glGetUniformLocation(_program, uniform.c_str());
}

GLuint GLSLShader::operator()(const string uniform){
	return _uniformLocationList[uniform];
}
GLuint GLSLShader::GetProgram() const {
	return _program;
}
#include <fstream>
void GLSLShader::LoadFromFile(GLenum whichShader, const string filename){
	ifstream fp;
	fp.open(filename.c_str(), ios_base::in);
	if(fp) {
		string buffer(std::istreambuf_iterator<char>(fp), (std::istreambuf_iterator<char>()));
		//copy to source
		LoadFromString(whichShader, buffer);
		std::cout<<GFXCALL<<filename<<" loaded\n";
	} else {
		cout<<GFXCALL"Error loading shader: "<<filename<<endl;
	}
}

void   GLSLShader::setUniform(const char *name,float x,float y, float z)
{
	int loc =  glGetUniformLocation(_program, name);
	if( loc >= 0 ) 	glUniform3f(loc,x,y,z);
}
void   GLSLShader::setUniform(const char *name, const glm::vec3 & v)
{
	this->setUniform(name,v.x,v.y,v.z);
}
void   GLSLShader::setUniform(const char *name, const glm::vec4 & v)
{
	int loc =  glGetUniformLocation(_program, name);
	if( loc >= 0 )	glUniform4f(loc,v.x,v.y,v.z,v.w);

}
void   GLSLShader::setUniform(const char *name, const glm::mat4 & m)
{
	int loc = glGetUniformLocation(_program, name);
	if( loc >= 0 )	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]); 
}
void   GLSLShader::setUniform(const char *name, const glm::mat3 & m)
{
	int loc = glGetUniformLocation(_program, name);
	if( loc >= 0 )	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}
void   GLSLShader::setUniform(const char *name, float val )
{
	int loc = glGetUniformLocation(_program, name);
	if( loc >= 0 )	glUniform1f(loc, val);
}
void   GLSLShader::setUniform(const char *name, int val )
{
	int loc = glGetUniformLocation(_program, name);
	if( loc >= 0 )	glUniform1i(loc, val);
}
void   GLSLShader::setUniform(const char *name, bool val )
{
	int loc = glGetUniformLocation(_program, name);
	if( loc >= 0 )	glUniform1i(loc, val);

}
