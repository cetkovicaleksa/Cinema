#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/mesh.h>

#include "Util.h"


constexpr double
	MIN_FRAME_DURATION_SECONDS = 1.0 / 75.0; // 75 fps

constexpr float
	CAMERA_SPEED = 0.05f;

glm::vec3
	min{ -5.0f, 0.0f, -5.0f },
	max{ 5.0f, 5.0f, 5.0f },
//
	cameraPos{ 0.0f, 0.0f, 3.0f },
	cameraFront{ 0.0f, 0.0f, -1.0f },
	cameraUp{ 0.0f, 1.0f, 0.0f };

float
	deltaTime = 0.0f,
	lastFrame = 0.0f;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() 
{
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "GLFW failed to initialize." << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	auto *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	GLFWwindow *window = glfwCreateWindow(
		mode->width,
		mode->height,
		"Cinema 3D",
		monitor,
		NULL
	);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return 2;
	}
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW failed to initialize." << std::endl;
		return 3;
	}

	glClearColor(0.2f, 0.8f, 0.6f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); glCullFace(GL_BACK); glFrontFace(GL_CCW);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	unsigned tex = loadTexture("res/textures/aki.png");

	while(!glfwWindowShouldClose(window)) 
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = -lastFrame + (lastFrame = currentFrame);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*auto
			wasCulling = glIsEnabled(GL_CULL_FACE),
			wasDepthTesting = glIsEnabled(GL_DEPTH_TEST);

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);*/
		
		//overlayShader.use();
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindTexture(GL_TEXTURE_2D, akiTex);
		//glBindVertexArray(overlayVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		/*if (wasCulling == GL_TRUE)
			glEnable(GL_CULL_FACE);

		if (wasDepthTesting == GL_TRUE)
			glEnable(GL_DEPTH_TEST);*/

		glfwSwapBuffers(window);
		glfwPollEvents();

		while (glfwGetTime() - currentFrame < MIN_FRAME_DURATION_SECONDS) {}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{

}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{

}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;

	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_1:
			glIsEnabled(GL_DEPTH_TEST) == GL_TRUE ? glDisable(GL_DEPTH_TEST) : glEnable(GL_DEPTH_TEST);
			break;
		case GLFW_KEY_2:
			glIsEnabled(GL_CULL_FACE) == GL_TRUE ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);
			break;
		case GLFW_KEY_W:
			//cameraPos += CAMERA_SPEED * cameraFront;
			break;
		case GLFW_KEY_S:
			//cameraPos -= CAMERA_SPEED * cameraFront;
			break;
		case GLFW_KEY_A:
			//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * CAMERA_SPEED;
			break;
		case GLFW_KEY_D:
			//cameraPos -= CAMERA_SPEED * cameraFront;
			break;
		}
}

