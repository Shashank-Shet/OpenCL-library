#include<CL/CommandQueue.h>

/*
 * Construct an empty command queue
 */
CommandQueue::CommandQueue():copy(true){}

/*
 * Copy a command queue
 */
CommandQueue::CommandQueue(CommandQueue &obj):copy(true), q(obj.q){}

void CommandQueue::operator=(CommandQueue &obj)
{
  this->copy = true;
  this->q = obj.q;
}

cl_command_queue CommandQueue::getCommandQueue()
{
  return this->q;
}

void CommandQueue::createCommandQueue(cl_context context, cl_device_id device)
{
  CommandQueue temp(context, device);
  this->copy = false;
  this->q = temp.q;
  temp.copy = true;
}

/**
 * Create a command queue object with given context and
 * device object
 * Report errors if any
 */
CommandQueue::CommandQueue(cl_context context, cl_device_id device):copy(false)
{
  cl_int status;
  this->q = clCreateCommandQueueWithProperties(context, device, 0, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

/**
 * Create a command queue object with given context and device 
 * object and queuing parameters, (eg: enable out of order 
 * execution)
 * Report errors if any
*/
#if __CL_VERSION == 200
CommandQueue::CommandQueue(cl_context context, cl_device_id device, const cl_queue_properties *properties)
#else
CommandQueue::CommandQueue(cl_context context, cl_device device, cl_command_queue_properties properties)
#endif
{
  this->copy = false;
  cl_int status;
  this->q = clCreateCommandQueueWithProperties(context, device, properties, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

cl_event CommandQueue::enqueueKernel(cl_kernel kernel, int dimension, size_t *global_work_size, size_t *local_work_size)
{
  cl_int status;
  cl_event evt;
  status = clEnqueueNDRangeKernel(this->q, kernel, dimension, NULL, global_work_size, local_work_size, 0, NULL, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

cl_event CommandQueue::enqueueKernel(cl_kernel kernel, int dimension, size_t *offset, size_t *global_work_size, size_t *local_work_size)
{
  cl_int status;
  cl_event evt;
  status = clEnqueueNDRangeKernel(this->q, kernel, dimension, offset, global_work_size, local_work_size, 0, NULL, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

cl_event CommandQueue::enqueueKernel(cl_kernel kernel, int dimension, size_t *offset, size_t *global_work_size, size_t *local_work_size,
				     cl_uint num_events, cl_event *event_list)
{
  cl_int status;
  cl_event evt;
  status = clEnqueueNDRangeKernel(this->q, kernel, dimension, offset, global_work_size, local_work_size, 0, NULL, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

cl_event CommandQueue::readBuffer(void* host_ptr, cl_mem buffer, unsigned int length)
{
  cl_event evt;
  cl_int status;
  status = clEnqueueReadBuffer(this->q, buffer, CL_TRUE, 0, (size_t)length, host_ptr, 0, NULL, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

cl_event CommandQueue::writeBuffer(void* host_ptr, cl_mem buffer, unsigned int length)
{
  cl_event evt;
  cl_int status;
  status = clEnqueueWriteBuffer(this->q, buffer, CL_TRUE, 0, (size_t)length, host_ptr, 0, NULL, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

cl_event CommandQueue::writeBuffer(void* host_ptr, cl_mem buffer, unsigned int length, unsigned int offset, bool block,
				  int num_evt, cl_event* wait_list)
{
  cl_event evt;
  cl_int status;
  status = clEnqueueWriteBuffer(this->q, buffer, block, offset, (size_t)length, host_ptr, num_evt, wait_list, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

cl_event CommandQueue::readBuffer(void* host_ptr, cl_mem buffer, unsigned int length, unsigned int offset, bool block,
				  int num_evt, cl_event* wait_list)
{
  cl_event evt;
  cl_int status;
  status = clEnqueueReadBuffer(this->q, buffer, block, offset, (size_t)length, host_ptr, num_evt, wait_list, &evt);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
  return evt;
}

/**
 * Release the queue object
 */
CommandQueue::~CommandQueue()
{
  if(this->copy)
    clReleaseCommandQueue(this->q);
}
