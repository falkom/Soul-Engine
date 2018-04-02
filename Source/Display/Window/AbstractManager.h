#pragma once

#include <vulkan\vulkan.hpp>
#include <GLFW\glfw3.h>

#include "Metrics.h"
#include "AbstractWindow.h"
#include "Display\Layout\Layout.h"

class AbstractManager
{
public:

	/* AbstractManager can be neither copied, nor assigned. */
	AbstractManager(AbstractManager const&) = delete;
	void operator=(AbstractManager const&) = delete;


	/* Close operations. */
	virtual bool ShouldClose() = 0;
	virtual void SignalClose() = 0;
	virtual void Close(void*) = 0;

	/* Process. to create a window. */
	virtual AbstractWindow* CreateWindow(WindowType, const std::string&, int monitor, uint x, uint y, uint width, uint height) = 0;

	/* Set the Window's Layout. */
	virtual void SetWindowLayout(AbstractManager*, Layout*) = 0;

	/* Modifier operations. */
	void Draw();
	virtual void Resize(void*, int, int) = 0;
	virtual void Refresh(void*) = 0;
	virtual void WindowPos(void*, int, int) = 0;

private:

	/* Constructor. */
	AbstractManager();
	/* Destructor. */
	~AbstractManager();

	/* List of all windows handled by the AbstractManager. */
	std::list<std::unique_ptr<AbstractWindow>> windows;
	/* Pointer to the master--or 'main'--window. */
	AbstractWindow* masterWindow = nullptr;

	/* 
		Monitor Count Variables. 
		monitors is a void* for abstraction purposes.
	*/
	int monitorCount;
	void** monitors;

	/* Flag that keeps track of if the AbstractManager is running. */
	bool runningFlag;
};