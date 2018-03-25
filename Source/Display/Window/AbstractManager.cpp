#include "AbstractManager.h"

AbstractManager::AbstractManager() {}

AbstractManager::~AbstractManager() {}

Window * AbstractManager::CreateWindow(WindowType, const std::string & title, int monitor, uint height, uint width) {
	return nullptr;
}

bool AbstractManager::ShouldClose(Window *) const {
	return false;
}

void AbstractManager::CloseWindow(Window *) {}

void AbstractManager::GetWindowSize(Window *, uint & height, uint & width) const {}

void AbstractManager::GetWindowPos(Window *, uint & x, uint & y) const {}

std::string AbstractManager::GetWindowTitle(Window *) const {
	return std::string();
}

void AbstractManager::SetWindowSize(Window *, uint height, uint width) {}

void AbstractManager::SetWindowPos(Window *, uint x, uint y) {}

void AbstractManager::SetWindowTitle(Window *, const std::string & title) {}
