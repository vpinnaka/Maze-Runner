#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>


class shaderprogram {
public:
	GLuint Program;
	shaderprogram(const char* vertexshader, const char* fragmentshader);
	GLuint getShaderProgram();
	void useShaderprogram();
	void setUniformVec3inShader(const char*location, glm::vec3 value);
	void setUniformMat4inShader(const char*location, glm::mat4 value);
	void setUniformfloatinShader(const char*location, float value);
private:
	std::string readShaderSource(const char* shaderFile);
	GLint compileShader(const char* source, GLenum type);
	void linkshader(const char*vertex_shaderSrc, const char*fragment_shaderSrc);

};

shaderprogram::shaderprogram(const char* vertexshader,const char* fragmentshader) {

	std::string vshader = readShaderSource(vertexshader);
	const GLchar* vertex_shader = vshader.c_str();
	std::string fshader = readShaderSource(fragmentshader);
	const GLchar* fragment_shader = fshader.c_str();;
	try {
	    Program = glCreateProgram();
		linkshader(vertex_shader, fragment_shader);
	}catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		throw;
	}
	

}

std::string shaderprogram::readShaderSource(const char* shaderFile) {

	std::ifstream shaderfile;

	std::string str;
	std::string file;

	std::stringstream ShaderStream;

	shaderfile.open(shaderFile);

	ShaderStream << shaderfile.rdbuf();
	
	
	shaderfile.close();

	file = ShaderStream.str();
	
	return file;
}

GLint shaderprogram::compileShader(const char* source, GLenum type) {

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint  compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		fprintf(stderr, "Failed to compile shader!\n");
		fprintf(stderr, "%s\n", source);

		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);


		char *infoLog = new char[maxLength];
		glGetShaderInfoLog(shader, maxLength, NULL, infoLog);

		std::cout << infoLog << std::endl;

		free(infoLog);

		exit(EXIT_FAILURE);
	}
	return shader;

}


void shaderprogram::linkshader(const char*vertex_shaderSrc, const char*fragment_shaderSrc) {

	
	glAttachShader(Program, compileShader(fragment_shaderSrc, GL_FRAGMENT_SHADER));
	glAttachShader(Program, compileShader(vertex_shaderSrc, GL_VERTEX_SHADER));
	glLinkProgram(Program);

	/* link  and error check */
	GLint  linked;
	glGetProgramiv(Program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader failed to link!\n";
		GLint  logSize = 0;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &logSize);

		char *infoLog = new char[logSize];
		glGetProgramInfoLog(Program, logSize, NULL, infoLog);
		std::cout << infoLog << std::endl;
		free(infoLog);
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Shaders link successful!\n";
	}

	
}

GLuint shaderprogram::getShaderProgram() {
	return Program;

}

void shaderprogram::useShaderprogram() {
	if(Program != NULL)
		glUseProgram(Program);
	else {
		std::cerr << "Shader program not initialized\n";
		exit(EXIT_FAILURE);
	}

}

void shaderprogram::setUniformVec3inShader(const char*locationname, glm::vec3 value) {

	GLuint location = glGetUniformLocation(Program, locationname);
	if (location < 0) 
		std::cerr << "couldn't find "<< locationname <<"in Shader\n";
	glUniform3fv(location,1,glm::value_ptr(value));
}

void shaderprogram::setUniformMat4inShader(const char*locationname, glm::mat4 value) {

	GLuint location = glGetUniformLocation(Program, locationname);
	if (location < 0)
		std::cerr << "couldn't find " << locationname << "in Shader\n";
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void shaderprogram::setUniformfloatinShader(const char*locationname, float value) {

	GLuint location = glGetUniformLocation(Program, locationname);
	if (location < 0)
		std::cerr << "couldn't find " << locationname << "in Shader\n";
	glUniform1f(location, value);
}

