
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "MeshHandler.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "SceneLight1.h"
#include "SceneLight2.h"
#include "SceneTexture.h"
#include "SceneSkybox.h"
#include "SceneModel.h"
#include "SceneAssignment1.h"
#include "SceneAssignment2.h"
#include "SceneRaceAssignment2.h"
#include "SceneText.h"
#include "SceneUI.h"

GLFWwindow* m_window;
unsigned Application::m_width;
unsigned Application::m_height;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Scenes
Scene* Application::scenes[2] = { new SceneAssignment2, new SceneRaceAssignment2 };
int Application::mainScene = 0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h);
}
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}

void Application::Init()
{
	//MeshHandler::loadMeshes();
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	m_width = 800;
	m_height = 600;

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(m_width, m_height, "Test Window", NULL, NULL);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	for (int i = 0; i < (sizeof(scenes) / sizeof(scenes[0])); i++) {
		scenes[i]->Init();
	}

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		if(IsKeyPressed(VK_F1))
			mainScene = 0;
		else if (IsKeyPressed(VK_F2))
			mainScene = 1;
		double dt = m_timer.getElapsedTime();
		scenes[mainScene]->elapser(dt);
		scenes[mainScene]->Update(dt);
		scenes[mainScene]->Render();

		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	
	for (int i = 0; i < (sizeof(scenes) / sizeof(scenes[0])); i++) {
		scenes[i]->Exit();
		delete scenes[i];
	}
}

bool Application::changeToScene(std::string sceneName, std::string msg) {
	for (int i = 0; i < (sizeof(scenes) / sizeof(scenes[0])); i++) {
		if (scenes[i]->getName() == sceneName) {
			if (mainScene != i) {
				if (sceneName == "RunningScene") {
					static_cast<SceneRaceAssignment2*>(scenes[i])->StartRacingSession();
					static_cast<SceneRaceAssignment2*>(scenes[i])->setPlayerSpeed(std::stof(msg));
				}
					
				mainScene = i;
				return true;
			}
		}
	}
	return false;
}

Scene* Application::getSceneByName(std::string sceneName) {
	for (int i = 0; i < (sizeof(scenes) / sizeof(scenes[0])); i++) {
		if (scenes[i]->getName().compare(sceneName) == 0) {
			return scenes[i];
		}
	}
}

void Application::Exit()
{
	MeshHandler::unloadMeshes();
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
