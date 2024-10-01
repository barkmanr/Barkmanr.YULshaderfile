#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
public:
	WindowController();
	virtual ~WindowController();

	GLFWwindow* GetWindow() //Returns the window
	{
		if (window == nullptr)
		{
			NewWindow();
		}
		return window;
	}

	void NewWindow();
	Resolution GetResolution();

private:
	GLFWwindow* window;
};

#endif WINDOW_CONTROLLER_H
