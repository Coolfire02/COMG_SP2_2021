
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "Scene.h"
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

	static Scene* scenes[2];
	static bool changeToScene(std::string, std::string);
	static Scene* getSceneByName(std::string);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double* xpos, double* ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static unsigned m_width;
	static unsigned m_height;

private:
	static int mainScene;
	//Declare a window object
	StopWatch m_timer;
};

#endif