//---------------------------------------------------------------------------------------------------
//@file	N:\Documents\Soul Engine\Source Files\Utility\Includes\GLFWIncludes.h.
//Declares the glfw includes class.

#pragma once

#pragma warning(push, 0)  

#define NOMINMAX

#ifdef _WIN32
#include <windows.h>
#endif

#include "GL\glew.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#pragma warning(pop)        
