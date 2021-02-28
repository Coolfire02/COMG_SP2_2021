
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "MeshHandler.h"
#include "Game.h"

#include "MissionManager.h"
#include "InteractionManager.h"

//Include Scenes
#include "Scene2021.h"
#include "SceneGarage.h"
#include "SceneGunShop.h"
#include "SceneHouseFire.h"
#include "SceneTimePortal.h"
#include "SceneGuardBuilding.h"
#include "SceneCarShop.h"
#include "SceneUI.h"
#include "SceneCarShop.h"
#include "SceneOffice.h"
#include "SceneFinale.h"

// Initialisation of static variables.

GLFWwindow* m_window;
unsigned Application::m_width;
unsigned Application::m_height;
bool Application::cursorEnabled = false;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

double Application::mouse_last_x = 0.0, Application::mouse_last_y = 0.0,
		Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0,
		Application::mouse_diff_x = 0.0, Application::mouse_diff_y = 0.0;
double Application::camera_yaw = 0.0, Application::camera_pitch = 0.0;

/******************************************************************************/
/*!
\brief
Defines an error callback.
*/
/******************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/******************************************************************************/
/*!
\brief
Defines the key input callback.
*/
/******************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/******************************************************************************/
/*!
\brief
Get Key Pressed state, is returned true every frame so should not be confused with a Key Held state.
*/
/******************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/******************************************************************************/
/*!
\brief
Get key released state, is called true even if key was not pressed before, use sparingly.
*/
/******************************************************************************/
bool Application::IsKeyReleased(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) == 0);
}

Application::Application()
{
}

Application::~Application()
{
}

/******************************************************************************/
/*!
\brief
Gets resize callback.
*/
/******************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{
	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h);
}

/******************************************************************************/
/*!
\brief
Gets the mouse update from origin of window to new mouse location. Used for First person and Third person camera.
*/
/******************************************************************************/
bool Application::GetMouseUpdate()
{
	if (glfwGetInputMode(m_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return false;

	glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;

	//Calculate the yaw and pitch
	camera_yaw = (float)mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
	camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

	// Do a wraparound if the mouse cursor has gone out of the deadzone
	if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width - m_window_deadzone))
	{
		mouse_current_x = m_window_width >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}
	if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height - m_window_deadzone))
	{
		mouse_current_y = m_window_height >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}

	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

	return false;
}

/******************************************************************************/
/*!
\brief
Gets Mouse Pressed state. 
0 - Left 
1 - Right Mouse
2 - Middle Mouse
*/
/******************************************************************************/
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}

/******************************************************************************/
/*!
\brief
Gets Cursor Position on screen
*/
/******************************************************************************/
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}

/******************************************************************************/
/*!
\brief
Get Window Width
*/
/******************************************************************************/
int Application::GetWindowWidth()
{
	return m_width;
}

/******************************************************************************/
/*!
\brief
Get Window Height
*/
/******************************************************************************/
int Application::GetWindowHeight()
{
	return m_height;
}

/******************************************************************************/
/*!
\brief
Initialises the OpenGL window here.
*/
/******************************************************************************/
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

	m_width = 1280;
	m_height = 720;

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(m_width, m_height, "Time Vengeance", NULL, NULL);
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

/******************************************************************************/
/*!
\brief
Sets the cursor input mode of the OpenGL window to NORMAL or DISABLED.
*/
/******************************************************************************/
void Application::setCursorEnabled(bool enabled) {
	cursorEnabled = enabled;
	if(cursorEnabled)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/******************************************************************************/
/*!
\brief
Loads all scenes and runs the game loop here.
*/
/******************************************************************************/
void Application::Run()
{
	/*for (int i = 0; i < (sizeof(scenes) / sizeof(scenes[0])); i++) {
		scenes[i]->Init();
	}*/
	MeshHandler::loadMeshes();
	AudioHandler::load();
	Text::loadFonts();
	MissionManager::loadMissionLang();

	g.addScene(new SceneHouseFire);
	g.addScene(new SceneGuardBuilding);
	g.addScene(new SceneTimePortal);
	g.addScene(new Scene2021);
	g.addScene(new SceneGunShop);
	g.addScene(new SceneGarage);
	g.addScene(new SceneCarShop);
	g.addScene(new SceneOffice);
	g.addScene(new SceneFinale);
	g.addScene(new SceneUI);

	//g.addScene(new SceneHouseFire);
	g.Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !Game::gameExit)
	{
		GetMouseUpdate();
		double dt = m_timer.getElapsedTime();
		g.Update(dt);
		g.Render();
		

		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.
		//setCursorEnabled(true);
	} //Check if the ESC key had been pressed or if the window had been closed

	/*for (int i = 0; i < (sizeof(scenes) / sizeof(scenes[0])); i++) {
		scenes[i]->Exit();
		delete scenes[i];
	}*/
}

/******************************************************************************/
/*!
\brief
Clean up function called when game is exited.
*/
/******************************************************************************/
void Application::Exit()
{
	g.Exit();
	MeshHandler::unloadMeshes();
	AudioHandler::cleanup();

	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
