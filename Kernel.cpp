#include<CL/Kernel.h>
/*
 * Construct a blank kernel object and mark it as a copy
 */
Kernel::Kernel():copy(true)
{}

/*
 * Copy a kernel object from one to another and mark as a copy
*/
Kernel::Kernel(Kernel &obj):copy(true), kernel(obj.kernel)
{}

/*
 * Copy a kernel to another 
 */
void Kernel::operator=(Kernel &obj)
{
  this->copy = true;
  this->kernel = obj.kernel;
}

/*
 * Create kernel for a blank kernel object and mark it as not a copy
 */
void Kernel::createKernel(cl_program program, std::string kernel_name)
{
  Kernel temp(program, kernel_name);
  this->kernel = temp.kernel;
  this->copy = false;
  temp.copy = true;
}

/**
 * Create a kernel using the provided program object and
 * kernel name. Mark as not a copy
 * Report errors if any
*/
Kernel::Kernel(cl_program program, std::string kernel_name):copy(false)
{
  cl_int status;
  this->kernel = clCreateKernel(program, kernel_name.c_str(), &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

/**
 * Create a kernel using the provided program object and 
 * kernel name. Also set the arguments to the kernel using
 * the specified buffers
 * Report errors if any
*/
Kernel::Kernel(cl_program program, std::string kernel_name, Buffer *buffers, int num_buffers):copy(false)
{
  cl_int status;
  this->kernel = clCreateKernel(program, kernel_name.c_str(), &status);
  if(status!=CL_SUCCESS)
    {
      std::cout<<errors[status]<<std::endl;
      return;
    }
  for(int i=0; i<num_buffers; i++)
    {
      status = clSetKernelArg(this->kernel, i, sizeof(cl_mem), (cl_mem*)&buffers[i]);
      if(status!=CL_SUCCESS)
	{
	  std::cout<<errors[status]<<std::endl;
	  return;
	}
    }
}

/**
 * Independent argument setting method. Fix the parameters
 * using number of buffers and actual buffers
 */
void Kernel::setArgs(int num_buffers, Buffer* buffers)
{
  cl_int status;
  for(int i=0; i<num_buffers; i++)
    {
      status = clSetKernelArg(this->kernel, i, sizeof(cl_mem), (cl_mem*)&buffers[i]);
      if(status!=CL_SUCCESS)
	{
	  std::cout<<errors[status]<<std::endl;
	  return;
	}
    }
}

/**
 * Independent argument setting method. Fix the parameters
 * using number of buffers and actual buffers
 */
void Kernel::setArgs(int arg_size, void* arg, int index)
{
  cl_int status;
  status = clSetKernelArg(this->kernel, index, arg_size, arg);
  if(status!=CL_SUCCESS)
    {
      std::cout<<errors[status]<<std::endl;
      return;
    }
}

/**
 * Return the encapsulated kernel object
 */
cl_kernel Kernel::getKernel()
{
  return this->kernel;
}

/**
 * Release the kernel
 */
Kernel::~Kernel()
{
  if(!copy)
    clReleaseKernel(this->kernel);
}
