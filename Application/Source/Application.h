
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "Scene.h"
#include "Game.h"
#include <string>

class Application
{
public:
	Application();
	~Application();
	static bool IsKeyPressed(unsigned short key);
	void Init();
	void Run();
	void Exit();

	Game   g;
	static bool changeToScene(std::string, std::string);
	static void setCursorEnabled(bool enabled);
	static Scene* getSceneByName(std::string);
	static bool IsMousePressed(unsigned short key);
	static bool IsKeyReleased(unsigned short key);
	static void GetCursorPos(double* xpos, double* ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static bool cursorEnabled;
	static unsigned m_width;
	static unsigned m_height;

	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;
	const static int m_window_deadzone = 100;
	const static int m_window_width = 800;
	const static int m_window_height = 600;
	bool GetMouseUpdate();

private:
	//Declare a window object
	StopWatch m_timer;
};

#endif