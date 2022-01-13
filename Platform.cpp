#include<CL/Platform.h>
Platform::Platform(Platform &object)
{
  this->platform_id = object.platform_id;
  this->num_devices = object.num_devices;
  this->devices = new Device[this->num_devices];
#pragma omp parallel for
  for(int i=0; i<num_devices; i++)
    this->devices[i] = object.devices[i];
  this->profile = new char[strlen(object.profile)];
  this->version = new char[strlen(object.version)];
  this->vendor = new char[strlen(object.vendor)];
  this->extensions = new char[strlen(object.extensions)];
  this->name = new char[strlen(object.name)];
  #pragma omp parallel sections 
  {
    #pragma omp section
    { strcpy(this->profile, object.profile); }
    #pragma omp section
    { strcpy(this->version, object.version); }
    #pragma omp section
    { strcpy(this->vendor, object.vendor); }
    #pragma omp section
    { strcpy(this->extensions, object.extensions); }
    #pragma omp section
    { strcpy(this->name, object.name); }
  }
}

void Platform::setPlatformId(cl_platform_id platform_id)
{
  this->platform_id = platform_id;
  cl_int status = clGetDeviceIDs(this->platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &(this->num_devices));

  if(status!=CL_SUCCESS)
    {
      std::cout<<errors[status]<<std::endl;
      return;
    }
  
  cl_device_id device_id_list[num_devices];
  clGetDeviceIDs(this->platform_id, CL_DEVICE_TYPE_ALL, num_devices, device_id_list, &(this->num_devices));
  
  this->devices = new Device[num_devices];
  for(int i=0; i<num_devices; i++)
    devices[i].setDeviceId(device_id_list[i]);
  
  getInfo();
}

void Platform::operator=(Platform& object)
{
  this->platform_id = object.platform_id;
  this->num_devices = object.num_devices;
  this->devices = new Device[this->num_devices];
#pragma omp parallel for
  for(int i=0; i<num_devices; i++)
    this->devices[i] = object.devices[i];
  this->profile = new char[strlen(object.profile)];
  this->version = new char[strlen(object.version)];
  this->vendor = new char[strlen(object.vendor)];
  this->extensions = new char[strlen(object.extensions)];
  this->name = new char[strlen(object.name)];
  #pragma omp parallel sections 
  {
    #pragma omp section
    { strcpy(this->profile, object.profile); }
    #pragma omp section
    { strcpy(this->version, object.version); }
    #pragma omp section
    { strcpy(this->vendor, object.vendor); }
    #pragma omp section
    { strcpy(this->extensions, object.extensions); }
    #pragma omp section
    { strcpy(this->name, object.name); }
  }
}

void Platform::getInfo()
{
  size_t string_length;
  profile = new char[20];
  clGetPlatformInfo(this->platform_id, CL_PLATFORM_PROFILE, 20, profile, &string_length);

  clGetPlatformInfo(this->platform_id, CL_PLATFORM_VERSION, 0, NULL, &string_length);
  version = new char[string_length];
  clGetPlatformInfo(this->platform_id, CL_PLATFORM_VERSION, string_length, version, &string_length);

  clGetPlatformInfo(this->platform_id, CL_PLATFORM_NAME, 0, NULL, &string_length);
  name = new char[string_length];
  clGetPlatformInfo(this->platform_id, CL_PLATFORM_NAME, string_length, name, &string_length);

  clGetPlatformInfo(this->platform_id, CL_PLATFORM_VENDOR, 0, NULL, &string_length);
  vendor = new char[string_length];
  clGetPlatformInfo(this->platform_id, CL_PLATFORM_VENDOR, string_length, vendor, &string_length);

  clGetPlatformInfo(this->platform_id, CL_PLATFORM_EXTENSIONS, 0, NULL, &string_length);
  extensions = new char[string_length];
  clGetPlatformInfo(this->platform_id, CL_PLATFORM_EXTENSIONS, string_length, extensions, &string_length);

}

Device& Platform::selectDevice(int index)
{
  if(index >= num_devices)
    {
      std::cout<<"Invalid Index"<<std::endl;
      index = 0;
    }
  return this->devices[index];
}

