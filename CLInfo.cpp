#pragma once
#include<iostream>
#ifdef __APPLE__
#include<OpenCL/opencl.h>
#else
#include<CL/cl.h>
#endif


/**
 * Query the platform and device(s) about information
 * regarding compatibility, support and other such
 * aspects
*/
void clInfo()
{
  cl_uint num_platforms, max_platforms, num_devices, max_devices;
  cl_platform_id *platforms = NULL;
  cl_device_id *devices = NULL;
  clGetPlatformIDs(0, NULL, &num_platforms);                     // First find number of available platforms
  max_platforms = num_platforms;
  platforms = new cl_platform_id[num_platforms];
  clGetPlatformIDs(max_platforms, platforms, &num_platforms);    // Obtain an array of IDs for each of them

  std::cout<<"Platforms:\t"<<num_platforms<<std::endl<<std::endl;
  for(int i=0; i<num_platforms; i++)
    {
      char string[1000];
      size_t len;
      std::cout<<"Platform "<<i<<" Info:"<<std::endl;
      clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 1000, string, &len);
      std::cout<<"PROFILE:\t"<<string<<std::endl;
      
      clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 1000, string, &len);
      std::cout<<"VERSION:\t"<<string<<std::endl;

      clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 1000, string, &len);
      std::cout<<"NAME:   \t"<<string<<std::endl;
      
      clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 1000, string, &len);
      std::cout<<"VENDOR: \t"<<string<<std::endl;

      clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 1000, string, &len);
      std::cout<<"EXTENSIONS:\t"<<string<<std::endl;

      std::cout<<std::endl;

      clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
      devices = new cl_device_id[num_devices];
      max_devices = num_devices;
      clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, max_devices, devices, &num_devices);

      std::cout<<"Devices: \t"<<num_devices<<std::endl<<std::endl;
      for(int i=0; i<num_devices; i++)
	{
	  std::cout<<"Device "<<i<<" Info:"<<std::endl;
	  char string[1000];     // For accepting char[] answers
	  cl_bool ans_bool;      // For accepting boolean answers
	  cl_uint ans_uint;      // For accepting uint answers
	  size_t len;
	  clGetDeviceInfo(devices[i], CL_DEVICE_AVAILABLE, 1, &ans_bool, &len);
	  std::cout<<"DEVICE AVAILABILITY:\t"<<(ans_bool?"YES":"NO")<<std::endl;

	  clGetDeviceInfo(devices[i], CL_DEVICE_COMPILER_AVAILABLE, 1, &ans_bool, &len);
	  std::cout<<"COMPILER AVAILABILITY:\t"<<(ans_bool?"YES":"NO")<<std::endl;
	  
	  clGetDeviceInfo(devices[i], CL_DEVICE_ENDIAN_LITTLE, 1, &ans_bool, &len);
	  std::cout<<"LITTLE ENDIAN:\t\t"<<(ans_bool?"YES":"NO")<<std::endl;

	  clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CLOCK_FREQUENCY, 4, &ans_uint, &len);
	  std::cout<<"MAX CLK FREQ:\t\t"<<ans_uint<<std::endl;

	  clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, 4, &ans_uint, &len);
	  std::cout<<"MAX COMPUTE UNITS:\t"<<ans_uint<<std::endl;
	  
	  clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, 4, &ans_uint, &len);
	  std::cout<<"MAX WORK GROUP SIZE:\t"<<ans_uint<<std::endl;	  

	  clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 4, &ans_uint, &len);
	  std::cout<<"MAX ITEM DIMENSIONS:\t"<<ans_uint<<std::endl;	  

	  clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_ITEM_SIZES, 4, &ans_uint, &len);
	  std::cout<<"MAX_WORK_ITEM_SIZES:\t"<<ans_uint<<std::endl;

	  clGetDeviceInfo(devices[i], CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, 4, &ans_uint, &len);
	  std::cout<<"VECTOR_WIDTH_DOUBLE:\t"<<ans_uint<<std::endl;
	  
	  clGetDeviceInfo(devices[i], CL_DEVICE_PROFILE, 1000, string, &len);
	  std::cout<<"PROFILE:\t\t"<<string<<std::endl;

	  clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR, 1000, string, &len);
	  std::cout<<"VENDOR:\t\t\t"<<string<<std::endl;
	  
	  clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 1000, string, &len);
	  std::cout<<"NAME:\t\t\t"<<string<<std::endl;
	  
	  clGetDeviceInfo(devices[i], CL_DEVICE_VERSION, 1000, string, &len);
	  std::cout<<"OPENCL VERSION:\t\t"<<string<<std::endl;

	  std::cout<<std::endl<<std::endl;
	}
      delete[] devices;
      std::cout<<"###########################################################"<<std::endl;
    }
  
  delete[] platforms;
}
