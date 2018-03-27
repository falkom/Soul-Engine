#pragma once

#include "Display\Layout\Layout.h"

#include "Metrics.h"
#include "Window.h"

class AbstractManager
{
public:
	/* Constructor */
	AbstractManager() = default;

	/* Destructor */
	~AbstractManager() = default;

	/* Window Management */
	virtual Window* CreateWindow(
		WindowType type, 
		const std::string& title, 
		int monitor,
		uint height,
		uint width,
		Window* masterWindow, 
		std::list<std::unique_ptr<Window>>& windows) = 0;

	virtual bool ShouldClose(Window* masterWindow) const = 0;
	virtual void SignalClose(std::list<std::unique_ptr<Window>>& windows, bool& runningFlag) = 0;
	virtual void CloseWindow(Window* window) = 0;
		
	/* Accessors */
	void GetWindowSize(Window* window, uint& height, uint& width) const;
	void GetWindowPos(Window* window, uint& x, uint& y) const;
	std::string GetWindowTitle(Window* window) const;

	/* Modifiers */
	virtual void RefreshWindow(Window* window) = 0;
	virtual void SetWindowSize(Window* window, uint height, uint width) = 0;
	virtual void SetWindowPos(Window* window, uint x, uint y) = 0;
	virtual void SetWindowTitle(Window* window, const std::string& title) = 0;

	/*
	To be implemented at a later date:
	- Set/Get Window Type
	- Set Window Icon
	- Set/Get Focus Window
	- Hide/Show Window
	*/
};