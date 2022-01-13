#include<CL/Buffer.h>
Buffer::Buffer():copy(true)
{}

Buffer::Buffer(Buffer &obj):copy(true)
{
  this->buffer = obj.buffer;
  this->context = obj.context;
}

Buffer::Buffer(cl_context context, cl_mem_flags flags, int buf_len):copy(false)
{
  cl_int status;
  this->context = context;
  this->buffer = clCreateBuffer(this->context, flags, buf_len, NULL, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

Buffer::Buffer(cl_context context, cl_mem_flags flags, int buf_len, void* init_ptr):copy(false)
{
  cl_int status;
  this->context = context;
  this->buffer = clCreateBuffer(this->context, flags | CL_MEM_COPY_HOST_PTR, buf_len, init_ptr, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}
  
Buffer::Buffer(cl_context context, cl_mem_flags flags, int buf_len, void *ptr, bool custom):copy(false)
{
  cl_int status;
  this->context = context;
  this->buffer = clCreateBuffer(this->context, flags, buf_len, ptr, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

void Buffer::initBuffer(cl_context context, cl_mem_flags flags, int buf_len)
{
  cl_int status;
  this->copy = false;
  this->context = context;
  this->buffer = clCreateBuffer(this->context, flags, buf_len, NULL, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

void Buffer::initBuffer(cl_context context, cl_mem_flags flags, int buf_len, void* init_ptr)
{
  cl_int status;
  this->copy = false;
  this->context = context;
  this->buffer = clCreateBuffer(this->context, flags | CL_MEM_COPY_HOST_PTR, buf_len, init_ptr, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}
  
void Buffer::initBuffer(cl_context context, cl_mem_flags flags, int buf_len, void *ptr, bool custom)
{
  cl_int status;
  this->copy = false;
  this->context = context;
  this->buffer = clCreateBuffer(this->context, flags, buf_len, ptr, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}


void Buffer::operator=(Buffer &obj)
{
  this->copy = true;
  this->context = obj.context;
  this->buffer = obj.buffer;
}

Buffer::~Buffer()
{
  if(!copy)
    clReleaseMemObject(this->buffer);
}
