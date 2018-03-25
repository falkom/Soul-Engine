#pragma once

#include "Display\Window\AbstractManager.h"

class GLFWManager : public AbstractManager
{
public:
	/* Constructor */
	GLFWManager();

	/* Destructor */
	~GLFWManager();

	/* Window Management */
	Window* CreateWindow(WindowType, const std::string& title, int monitor, uint height, uint width);
	bool ShouldClose(Window* window) const;
	void CloseWindow(Window*);

	void RefreshWindow(Window* window);
	void SetWindowSize(Window* window, uint height, uint width);
	void SetWindowPos(Window* window, uint x, uint y);
	void SetWindowTitle(Window* window, const std::string& title);

};