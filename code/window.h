#pragma once

 
#include "camera.h"
#include "shaderprogram.h"
#include "cube.h"
#include "maze.h"

#define EXIT_FLAG 0

bool key_states[1024];
GLfloat lastX, lastY;

GLfloat zoomSensitivity = 0.98f;
bool firstMouse;
camera* Camera;
bool birdeye = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

class Window {

	
	shaderprogram* program;
	maze* Maze;
	int width, height;
	
public:
	GLFWwindow* window;
	Window(const char*title, int width, int height);
	void update(GLfloat);
	void startgame();
	

	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//friend void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	~Window();


};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key != GLFW_KEY_UNKNOWN) {
		key_states[key] = action != GLFW_RELEASE;
	}
}

//void mouseCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat mouseXoffset = xpos - lastX;
//	GLfloat mouseYoffset = lastY - ypos;
//
//	lastX = xpos;
//	lastY = ypos;
//	//if(!birdeye)
//		//Camera->rotateCamera(mouseXoffset, mouseYoffset, deltaTime);
//
//
//}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset<0.0f)
		Camera->updateFieldOfView(2.0f - zoomSensitivity);
	else
		Camera->updateFieldOfView(zoomSensitivity);
}

Window::Window(const char*title, int width, int height) {

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FLAG);
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		exit(EXIT_FLAG);
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();


	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	lastX = width / 2;
	lastY = height / 2;
	firstMouse = true;

	Camera = new camera(width, height);
	program = new shaderprogram("vertex_shader.glsl", "fragment_shader.glsl");
	Maze = new maze("maze.txt",program);

}

void Window::update(GLfloat deltaTime) {

	if (key_states[GLFW_KEY_UP])
	{
		
			Camera->moveCamera(FORWARD, deltaTime);
	}
		
	if (key_states[GLFW_KEY_DOWN])
		Camera->moveCamera(BACKWARD, deltaTime);
	if (key_states[GLFW_KEY_LEFT]) {
		//bool collison = Maze->isacollision(Camera->getPositionVector(), GLFW_KEY_LEFT);
		//if (!collison)
		{
			Camera->moveCamera(LEFT, deltaTime);
		}
			
	}
		
	if (key_states[GLFW_KEY_RIGHT]) {
		//bool collison = Maze->isacollision(Camera->getPositionVector(), GLFW_KEY_RIGHT);
		//if (!collison)
			Camera->moveCamera(RIGHT, deltaTime);
	}
		
	if (key_states[GLFW_KEY_W])
	{
		
		Camera->setCameraView(Camera->getPositionVector(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (key_states[GLFW_KEY_S])
	{
		
		Camera->setCameraView(Camera->getPositionVector(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	}
	if (key_states[GLFW_KEY_A])
	{

		Camera->setCameraView(Camera->getPositionVector(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (key_states[GLFW_KEY_D])
	{

		Camera->setCameraView(Camera->getPositionVector(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	}
	if (key_states[GLFW_KEY_B])
	{
		birdeye = false;
		Camera->setCameraView(Maze->getstartposition(),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
		
}

void Window::startgame() {

	
	
	glfwSetKeyCallback(window, keyCallback);
	//glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		glfwPollEvents();

		update(deltaTime);


		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		program->useShaderprogram();

		program->setUniformVec3inShader("light.position", glm::vec3(1.2f, 1.0f, 2.0f));
		program->setUniformVec3inShader("viewPos", Camera->getPositionVector());


		program->setUniformVec3inShader("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		program->setUniformVec3inShader("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		program->setUniformVec3inShader("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		

		

		Camera->updatecamera();
		program->setUniformMat4inShader("view", Camera->getViewMatrix());
		program->setUniformMat4inShader("projection", Camera->getProjectionMatrix());

		
		Maze->draw();

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 4.0f);
		lightColor.y = sin(glfwGetTime() * 1.4f);
		lightColor.z = sin(glfwGetTime() * 2.6f);
		glm::vec3 diffuseColor = lightColor   * glm::vec3(0.7f); // Decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.5f); // Low influence
		program->setUniformVec3inShader("light.ambient", ambientColor);
		program->setUniformVec3inShader("light.diffuse", diffuseColor);
		program->setUniformVec3inShader("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		Maze->drawstart_end();
		
		glfwSwapBuffers(window);

	}
}



Window::~Window() {

	glfwSetWindowShouldClose(window, GL_TRUE);
}
