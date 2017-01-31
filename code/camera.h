#pragma once
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class camera {
	glm::mat4 View, Projection;
	int width, height;
	glm::vec3 position;
	glm::vec3 front, up, right;
	float fov;
	// Eular Angles
	
	GLfloat Yaw = -90.0f;
	GLfloat Pitch = 0.0f;
	GLfloat Roll = 0.0f;
	// Camera options
	GLfloat mousesensitivity = 0.25f;
	GLfloat movementSpeed = 1.5f;
	
public:
	camera(int width, int height);
	void updatecamera();
	void moveCamera(Camera_Movement direction, GLfloat deltaTime);
	void rotateCamera(GLfloat xoffset, GLfloat yoffset, GLfloat delta);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getPositionVector();
	void setCameraView(glm::vec3 startposition, glm::vec3 up, glm::vec3 front, glm::vec3 right);
	void updateFieldOfView(GLfloat yoffset);
private:
	void setViewMatrix();
	void setProjectionMatrix(int width, int height);
	void addEulerangles();
};

camera::camera(int width,int height){
	this->width = width;
	this->height = height;
	position = glm::vec3(0.5f,1.0f,8.0);
	up = glm::vec3(0.0,1.0,0.0);
	front = glm::vec3(0.0,0.0,-1.0);
	right = glm::vec3(1.0,0.0,0.0);

	Yaw = -90.0f;
	fov = 90.0f;
}

void camera::updatecamera() {
	
	setProjectionMatrix(width,height);

	setViewMatrix();
}

void camera::moveCamera(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == FORWARD)
		this->position += this->front * velocity;
	if (direction == BACKWARD)
		this->position -= this->front * velocity;
	if (direction == LEFT)
		this->position -= this->right * velocity;
	if (direction == RIGHT)
		this->position += this->right * velocity;
}

void camera::rotateCamera(GLfloat xoffset, GLfloat yoffset,GLfloat time)
{
	xoffset *= (this->mousesensitivity*time);
	yoffset *= (this->mousesensitivity*time);

	if (this->Pitch + xoffset > 89.0f) {
		this->Pitch = 89.0f;
	}

	if (this->Pitch + xoffset < -89.0f) {
		this->Pitch = -89.0f;
	}
	else {
		this->Pitch += xoffset;
	}

	this->Yaw += yoffset;

	addEulerangles();
	
}

void camera::addEulerangles()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->up)); 
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

void camera::updateFieldOfView(GLfloat offset) {

	float value = fov*offset;
	
	if (this->fov <= 15.0f)
		this->fov = 15.0f;
	else
		fov = value;
	if (this->fov >= 120.0f)
		this->fov = 120.0f;
	else
		fov = value;
}
void camera::setProjectionMatrix(int screenWidth,int screenHeight) {
	Projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.001f, 1000.0f);
}

void camera::setViewMatrix() {
	View = glm::lookAt(this->position, this->position + this->front, this->up);
}

void camera::setCameraView(glm::vec3 startposition, glm::vec3 up, glm::vec3 front,glm::vec3 right) {
	position = startposition;
	this->up = up;
	this->front = front;
	this->right = right;
}
glm::vec3 camera::getPositionVector() {
	return this->position;
}

glm::mat4 camera::getViewMatrix() {
	return View;
}

glm::mat4 camera::getProjectionMatrix() {
	return Projection;
}



