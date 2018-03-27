#pragma once

#include "Display\Window\AbstractManager.h"

class GLFWManager : public AbstractManager
{
public:
	/* Constructor */
	GLFWManager();

	/* Destructor */
	~GLFWManager() = default;

	/* Window Management */
	Window* CreateWindow(WindowType type, const std::string& title, int monitor, uint height, uint width, Window* masterWindow, std::list<std::unique_ptr<Window>>& windows);
	bool ShouldClose(Window* masterWindow) const;
	void SignalClose(std::list<std::unique_ptr<Window>>&, bool& runningFlag);
	void CloseWindow(Window* window);

	void RefreshWindow(Window* window);
	void SetWindowSize(Window* window, uint height, uint width);
	void SetWindowPos(Window* window, uint x, uint y);
	void SetWindowTitle(Window* window, const std::string& title);
	
private:
	int monitorCount;
	GLFWmonitor** monitors;

};