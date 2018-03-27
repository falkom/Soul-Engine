#include "GLFWManager.h"

#include "Utility\Logger.h"
#include "GLFW.h"


/* Constructor */
GLFWManager::GLFWManager() :
	monitorCount(0),
	monitors(nullptr) {
	monitors = glfwGetMonitors(&monitorCount);
}

/* Window Management */
Window* GLFWManager::CreateWindow(WindowType type, const std::string& title, int monitor, uint height, uint width, Window* masterWindow, std::list<std::unique_ptr<Window>>& windows) {
	if (monitor > monitorCount) {
		S_LOG_ERROR("The specified moniter '", monitor, "' needs to be less than ", monitorCount);
		return nullptr;
	}
	GLFWmonitor* monitorIn = monitors[monitor];

	if (masterWindow == nullptr) {
		windows.emplace_back(new GLFW(type, title, 0, 0, width, height, monitorIn, nullptr));
		masterWindow = windows.front().get();
	} else {
		GLFWwindow* sharedCtx = masterWindow->windowHandle;
		windows.emplace_back(new GLFW(type, title, 0, 0, width, height, monitorIn, sharedCtx));
	}


	return nullptr;
}

bool GLFWManager::ShouldClose(Window* masterWindow) const {
	if (masterWindow != nullptr) {
		return (bool)glfwWindowShouldClose(masterWindow->windowHandle);
	} else {
		// In the case that there is no window system, this should always return false
		return false;
	}
}

void GLFWManager::SignalClose(std::list<std::unique_ptr<Window>>& windows, bool& runningFlag) {
	for (auto& win : windows) {
		glfwSetWindowShouldClose(win->windowHandle, GLFW_TRUE);
	}
	runningFlag = false;
}

void GLFWManager::CloseWindow(Window* window) {}


/* Modifiers */
void GLFWManager::RefreshWindow(Window* window) {}

void GLFWManager::SetWindowSize(Window* window, uint height, uint width) {}

void GLFWManager::SetWindowPos(Window* window, uint x, uint y) {}

void GLFWManager::SetWindowTitle(Window* window, const std::string& title) {}
