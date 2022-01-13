#include<CL/Device.h>
cl_bool Device::isAvailable()
{
  bool *ret_val = getInfo<bool>(CL_DEVICE_AVAILABLE);
  bool answer = *ret_val;
  delete[] ret_val;
  return answer;  
}

cl_device_id Device::getDeviceId()
{
  return this->device_id;
}

void Device::operator=(Device& object)
{
  this->device_id = object.device_id;
}

cl_bool Device::isCompilerAvailable()
{
  bool *ret_val = getInfo<bool>(CL_DEVICE_COMPILER_AVAILABLE);
  bool answer = *ret_val;
  delete[] ret_val;
  return answer;  
}

cl_bool Device::isLittleEndian()
{
  bool *ret_val = getInfo<bool>(CL_DEVICE_COMPILER_AVAILABLE);
  bool answer = *ret_val;
  delete[] ret_val;
  return answer;  
}

cl_bool Device::hasErrorCorrection()
{
  bool *ret_val = getInfo<bool>(CL_DEVICE_ERROR_CORRECTION_SUPPORT);
  bool answer = *ret_val;
  delete[] ret_val;
  return answer;  
}

cl_bool Device::hasImageSuppport()
{
  bool *ret_val = getInfo<bool>(CL_DEVICE_IMAGE_SUPPORT);
  bool answer = *ret_val;
  delete[] ret_val;
  return answer;  
}


std::string Device::getExtensions()
{
  char *ret_val = getInfo<char>(CL_DEVICE_EXTENSIONS);
  std::string answer(ret_val);
  delete[] ret_val;
  return answer;
}

std::string Device::getVendor()
{
  char *ret_val = getInfo<char>(CL_DEVICE_VENDOR);
  std::string answer(ret_val);
  delete[] ret_val;
  return answer;
}

std::string Device::getDeviceVersion()
{
  char *ret_val = getInfo<char>(CL_DEVICE_VERSION);
  std::string answer(ret_val);
  delete[] ret_val;
  return answer;
}

std::string Device::getDriverVersion()
{
    char *ret_val = getInfo<char>(CL_DRIVER_VERSION);
  std::string answer(ret_val);
  delete[] ret_val;
  return answer;
}

std::string Device::getProfile()
{
    char *ret_val = getInfo<char>(CL_DEVICE_PROFILE);
  std::string answer(ret_val);
  delete[] ret_val;
  return answer;
}

std::string Device::getDeviceName()
{
  char *ret_val = getInfo<char>(CL_DEVICE_EXTENSIONS);
  std::string answer(ret_val);
  delete[] ret_val;
  return answer;
}


cl_ulong Device::getGlobalMemCacheSize()
{
  cl_ulong *ret_val = getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
  cl_ulong answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_ulong Device::getGlobalMemSize()
{
  cl_ulong *ret_val = getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_SIZE);
  cl_ulong answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_ulong Device::getLocalMemSize()
{
  cl_ulong *ret_val = getInfo<cl_ulong>(CL_DEVICE_LOCAL_MEM_SIZE);
  cl_ulong answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_ulong Device::getMaxConstBufferSize()
{
  cl_ulong *ret_val = getInfo<cl_ulong>(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
  cl_ulong answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_ulong Device::getMaxMemAllocSize()
{
  cl_ulong *ret_val = getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE);
  cl_ulong answer = *ret_val;
  delete[] ret_val;
  return answer;
}


cl_uint Device::getArch()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_ADDRESS_BITS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getCacheLineSize()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxClkFreq()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxComputeUnits()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxConstArgs()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_CONSTANT_ARGS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxReadImages()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_READ_IMAGE_ARGS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxWriteImages()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxSamplers()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_SAMPLERS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxWorkItemDimension()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_uint Device::getMaxWorkItemSize()
{
  cl_uint *ret_val = getInfo<cl_uint>(CL_DEVICE_MAX_WORK_ITEM_SIZES);
  cl_uint answer = *ret_val;
  delete[] ret_val;
  return answer;
}


size_t Device::get2dImageMaxHeight()
{
  size_t *ret_val = getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_HEIGHT);
  size_t answer = *ret_val;
  delete[] ret_val;
  return answer;
}

size_t Device::get2dImageMaxWidth()
{
  size_t *ret_val = getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_WIDTH);
  size_t answer = *ret_val;
  delete[] ret_val;
  return answer;
}

size_t Device::get3dImageMaxHeight()
{
  size_t *ret_val = getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_HEIGHT);
  size_t answer = *ret_val;
  delete[] ret_val;
  return answer;
}

size_t Device::get3dImageMaxWidth()
{
  size_t *ret_val = getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_WIDTH);
  size_t answer = *ret_val;
  delete[] ret_val;
  return answer;
}

size_t Device::get3dImageMaxDepth()
{
  size_t *ret_val = getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_DEPTH);
  size_t answer = *ret_val;
  delete[] ret_val;
  return answer;
}

size_t Device::getMaxParameterSize()
{
  size_t *ret_val = getInfo<size_t>(CL_DEVICE_MAX_PARAMETER_SIZE);
  size_t answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_device_mem_cache_type Device::getGlobalMemCacheType()
{
  cl_device_mem_cache_type *ret_val = getInfo<cl_device_mem_cache_type>(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
  cl_device_mem_cache_type answer = *ret_val;
  delete[] ret_val;
  return answer;
}

cl_device_type Device::getDeviceType()
{
  cl_device_type *ret_val = getInfo<cl_device_type>(CL_DEVICE_TYPE);
  cl_device_type answer = *ret_val;
  delete[] ret_val;
  return answer;
}

