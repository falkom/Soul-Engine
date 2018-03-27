#include "AbstractManager.h"

void AbstractManager::GetWindowSize(Window* window, uint& height, uint& width) const {
	height = window->height;
	width = window->width;
}

void AbstractManager::GetWindowPos(Window* window, uint& x, uint& y) const {
	x = window->xPos;
	y = window->yPos;
}

std::string AbstractManager::GetWindowTitle(Window* window) const {
	return window->title;
}
