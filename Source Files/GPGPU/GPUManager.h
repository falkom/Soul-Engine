//---------------------------------------------------------------------------------------------------
//@file	N:\Documents\Soul Engine\Source Files\GPGPU\GPUManager.h.
//Declares the GPU manager class.

#pragma once

#include "GPURasterBuffer.h"
#include "Metrics.h"

//.
namespace GPUManager {

	//Extracts the devices.
	void ExtractDevices();
	//Destroys the devices.
	void DestroyDevices();

	//Initializes the thread.
	void InitThread();

	//---------------------------------------------------------------------------------------------------
	//Creates raster buffer.
	//@param	parameter1	The first parameter.
	//@param	parameter2	The second parameter.
	//@return	Null if it fails, else the new raster buffer.

	GPURasterBuffer* CreateRasterBuffer(int,uint);

	//---------------------------------------------------------------------------------------------------
	//Creates a buffer.
	//@param	parameter1	The first parameter.
	//@param	parameter2	The second parameter.
	//@return	Null if it fails, else the new buffer.

	GPUBuffer* CreateBuffer(int, uint);

	//---------------------------------------------------------------------------------------------------
	//Gets best GPU.
	//@return	The best GPU.

	int GetBestGPU();
}