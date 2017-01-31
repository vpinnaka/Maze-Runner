#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>



class maze {
	int mazedimen;
	int d;
	int x_click =2, y_click =2,x_pos=0,y_pos=0;
	int** mazeindex;
	std::vector<glm::vec3>walls;
	std::vector<glm::vec3>floors;
	cube* Cube;
	shaderprogram* program;
public:
	glm::vec3 startposition;
	glm::vec3 endposition;
	glm::vec3 getstartposition();
	maze(const char * filename, shaderprogram* program);
	void draw();
	void drawstart_end();
	bool isacollision(glm::vec3 currentposition,int keypressed);
};

maze::maze(const char * filename, shaderprogram* program)
{
	this->program = program;
	
	std::ifstream mazefile;
	std::string singleline;
	
	
	mazefile.open(filename);
	if (!mazefile.is_open())
	{
		std::cout << "Error in reading scene file" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::getline(mazefile, singleline);
	mazedimen = atoi(singleline.c_str());
	mazeindex = new int*[mazedimen];

	d = mazedimen / 2;
	for (int i = 0; i < mazedimen; i++)
		mazeindex[i] = new int[mazedimen];

	for (int j = 0; !mazefile.eof();j++)
	{
		std::getline(mazefile, singleline);

		std::stringstream maze_line(singleline);
		for (int i = 0; i < mazedimen;i++)
			maze_line >> mazeindex[j][i];	

	}

	float pW = (float)2 * d / (float)mazedimen;
	float pH = (float)2 * d / (float)mazedimen;

	for (int i = 0; i < mazedimen; i++)
	{
		for (int j = 0; j < mazedimen; j++)
		{
			
			float pCx = -d + (pW / 2) + j*pW;
			float pCy = d - (pH / 2) - i*pH;
			float pCz = 0.0f;
			if (mazeindex[i][j] == 1) {
				
				walls.push_back(glm::vec3 (pCx, pCy, pCz));
			}
			else if (mazeindex[i][j] == 2)
			{
				floors.push_back(glm::vec3(pCx, pCy, pCz));
				startposition = glm::vec3(pCx, pCy, pCz);
			}
			else if (mazeindex[i][j] == 3)
			{
				floors.push_back(glm::vec3(pCx, pCy, pCz));
				endposition = glm::vec3(pCx, pCy, pCz);
			}
			else {
				floors.push_back(glm::vec3(pCx, pCy, pCz));
			}
		}
	}

	Cube = new cube(this->program);
}
glm::vec3 maze::getstartposition() {

	return (2 * d / (float)mazedimen)*startposition + glm::vec3((d / (float)mazedimen));
}


void maze::draw() {

	Cube->bind();

	program->setUniformVec3inShader("material.ambient", glm::vec3(0.1745, 0.01175, 0.01175));
	program->setUniformVec3inShader("material.diffuse", glm::vec3(0.61424, 0.04136, 0.04136));
	program->setUniformVec3inShader("material.specular", glm::vec3(0.727811, 0.626959, 0.626959));
	program->setUniformfloatinShader("material.shininess", 76.8f);

	for (glm::vec3 position : walls)
	{
		glm::mat4 transform;
		transform = glm::scale(transform, (2*d/(float)mazedimen)*glm::vec3(1.0f, 1.0f, 1.0f));
		transform = glm::translate(transform, (2*d/ (float)mazedimen)*glm::vec3(position));
		program->setUniformMat4inShader("model", transform);
		Cube->draw();
	}

	program->setUniformVec3inShader("material.ambient", glm::vec3(0.0, 0.1, 0.06));
	program->setUniformVec3inShader("material.diffuse", glm::vec3(0.0, 0.50980392, 0.50980392));
	program->setUniformVec3inShader("material.specular", glm::vec3(0.50196078, 0.50196078, 0.50196078));
	program->setUniformfloatinShader("material.shininess", 32.0f);

	glm::mat4 transform;
	transform = glm::scale(transform, glm::vec3(mazedimen, mazedimen, 0.025f));
	transform = glm::translate(transform, glm::vec3(-0.5,-0.4,0.0));
	program->setUniformMat4inShader("model", transform);
	Cube->draw();

	/*for (glm::vec3 position : floors)
	{
		glm::mat4 transform;
		transform = glm::scale(transform, (2 * d / (float)mazedimen)*glm::vec3(1.0f, 1.0f, 0.025f));
		transform = glm::translate(transform, (2 * d / (float)mazedimen)*glm::vec3(position));
		program->setUniformMat4inShader("model", transform);
		Cube->draw();
	}*/
}

void maze::drawstart_end() {
	program->setUniformVec3inShader("material.ambient", glm::vec3(0.0, 0.1, 0.06));
	program->setUniformVec3inShader("material.diffuse", glm::vec3(0.0, 0.50980392, 0.50980392));
	program->setUniformVec3inShader("material.specular", glm::vec3(0.50196078, 0.50196078, 0.50196078));
	program->setUniformfloatinShader("material.shininess", 32.0f);

	glm::mat4 transform1;
	transform1 = glm::scale(transform1, (2 * d / (float)mazedimen)*glm::vec3(0.5f));
	transform1 = glm::translate(transform1, (4 * d / (float)mazedimen)*startposition);
	program->setUniformMat4inShader("model", transform1);
	Cube->draw();

	glm::mat4 transform2;
	transform2 = glm::scale(transform2, (2 * d / (float)mazedimen)*glm::vec3(0.5f));
	transform2 = glm::translate(transform2, (4 * d / (float)mazedimen)*endposition);
	program->setUniformMat4inShader("model", transform2);
	Cube->draw();
}

bool maze::isacollision(glm::vec3 currentposition, int keypressed) {

	bool collison = false;
	switch (keypressed) {
	case GLFW_KEY_RIGHT: {
		if (x_click < 4)
		{
			x_click++;
			
		}			
		else {
			x_click = 0;
			collison = true;
			x_pos++;
		}
		break;
	}
	case GLFW_KEY_LEFT: {
		if (x_click > 0) {
			x_click--;
			collison = false;
		}			
		else {
			x_click = 0;
			
			x_pos--;
		}
		break;
	}
	}
	/*if (mazeindex[x_pos+1][14 - (y_pos)] == 1)
	{
		if (keypressed == GLFW_KEY_RIGHT)
			x_click--;
		else if (keypressed == GLFW_KEY_LEFT)
			x_click++;

		collison = true;
	}
	else {
		collison = false;
	}*/
	return collison;
}