#include "RayEngine.h"
#include "CUDA/RayEngine.cuh"

std::vector<RayJob*> jobList = std::vector<RayJob*>(0);

void RayEngine::Process(const Scene* scene){
	ProcessJobs(jobList, scene);
}

RayJob* RayEngine::AddRayJob(rayType whatToGet, uint rayAmount,
	uint samples, Camera* camera, uint resBuffN){

	RayJob* newJob = new RayJob(whatToGet, rayAmount, samples, camera, resBuffN);
	jobList.push_back(newJob);

	return newJob;
}

bool RayEngine::ChangeJob(RayJob* job, uint rayAmount, 
	float samples, Camera* camera){

	if (rayAmount<=job->RayAmountMax()){
		job->GetRayAmount() = rayAmount;
		job->GetSampleAmount() = samples;
		job->GetCamera() = camera;

		return true;
	}
	else{
		return false;
	}

}

void RayEngine::Clear(){
	ClearResults(jobList);
}

bool RayEngine::SwapResults(RayJob* job, uint a, uint b){
	job->SwapResults(a, b);
	return true;
}
void RayEngine::Clean(){
	CudaCheck(cudaDeviceSynchronize());
	for (int i = 0; i < jobList.size(); i++){
		delete jobList[i];
	}
	Cleanup();
}