#include<CL/Environment.h>

Environment::Environment()
{
  if(clGetPlatformIDs(0, NULL, &(this->num_platforms))==CL_OUT_OF_HOST_MEMORY)   // Find number of platforms
    {
      std::cout<<"Unable to allocate resources"<<std::endl;
      return;
    }

  cl_platform_id platform_id_list[num_platforms];                                // Get their respective ids 
  clGetPlatformIDs(num_platforms, platform_id_list, &num_platforms);   

  this->platforms = new Platform[num_platforms];                                 // Embed the ids in individual Platform objects
  for(int i=0; i<num_platforms; i++)
    platforms[i].setPlatformId(platform_id_list[i]);
}

/**
 * The runner program will call CLInfo to get detailed 
 * summary of available platforms and devices, based on
 * which user will input which platform and device is 
 * to be used
 */
Platform& Environment::selectPlatform(int index)
{
  if(index>=num_platforms)
    {
      std::cout<<"Invalid Index"<<std::endl;
      index=0;
    }
  return this->platforms[index];
}
