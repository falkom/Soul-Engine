#pragma once

#include "Display\Layout\Layout.h"

#include "Metrics.h"
#include "Window.h"

class AbstractManager
{
public:
	/* Constructor */
	AbstractManager();

	/* Destructor */
	~AbstractManager();

	/* Window Management */
	Window* CreateWindow(WindowType, const std::string& title, int monitor, uint height, uint width);
	bool ShouldClose(Window*) const;
	void CloseWindow(Window*);

	/* Accessors */
	void GetWindowSize(Window*, uint& height, uint& width) const;
	void GetWindowPos(Window*, uint& x, uint& y) const;
	std::string GetWindowTitle(Window*) const;

	/* Modifiers */
	void SetWindowSize(Window*, uint height, uint width);
	void SetWindowPos(Window*, uint x, uint y);
	void SetWindowTitle(Window*, const std::string& title);

	/*
	To be implemented at a later date:
	- Set Window Icon
	- Set/Get Focus Window
	- Hide/Show Window
	*/
private:

};