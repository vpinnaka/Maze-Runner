#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <string>
#include <iostream>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>

class cube {
	shaderprogram* program;
	GLuint VAO,VBO;
public:
	cube(shaderprogram* program);
	void init();
	void bind();
	void draw();
	 

};

cube::cube(shaderprogram* program) {

	this->program = program;
	init();
	//This line has to be in mazefile delete it
	

}

void cube::init() {

	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		1.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		0.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

		0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f, 0.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		0.0f, 1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,

		0.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		0.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		0.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		0.0f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		0.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		1.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		1.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		1.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,

		0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

		0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		1.0f,  1.0f,  1.0f, 0.0f,  1.0f,  0.0f,
		1.0f,  1.0f,  1.0f, 0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f
	};

	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	

}

void cube::bind() {

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//  attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void cube::draw() {

	
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}