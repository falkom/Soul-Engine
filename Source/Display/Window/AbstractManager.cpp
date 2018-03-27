#include "AbstractManager.h"

void AbstractManager::GetWindowSize(Window * window, uint & height, uint & width) const {}

void AbstractManager::GetWindowPos(Window * window, uint & x, uint & y) const {

}

std::string AbstractManager::GetWindowTitle(Window * window) const {
	return window->title;
}
