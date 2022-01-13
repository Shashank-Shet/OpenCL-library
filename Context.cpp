#include<CL/Context.h>

/**
 * Bad method. Should be returned. Unravels object to
 * return the encapsulated context object
*/
cl_context Context::getContext()
{
  return this->context;
}

/**
 * Create blank object marked as a copy by default
 */
Context::Context():copy(true)
{}

/**
 * Copy a context object. Mark as a copy
*/
Context::Context(Context &obj)
{
  this->copy = true;
  this->context = obj.context;
}

/**
 * Copy a context object. Mark as a copy
*/
void Context::operator=(Context &obj)
{
  this->copy = true;
  this->context = obj.context;
}

/*
 * Construct a context object. Takes devices and number as
 * args, assumes the rest.
 * Report errors if any
 */
Context::Context(int num_devices, Device *devices)
{
  cl_int status;
  this->context = clCreateContext(NULL,
				     num_devices,
				     (cl_device_id*)devices,
				     NULL,
				     NULL,
				     &status
				     );
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;  
}

/*
 * Construct a context object from a given device type.
 * Report errors if any.
 */
Context::Context(cl_device_type type)
{
  cl_int status;
  this->context = clCreateContextFromType(NULL,
					     type,
					     NULL,
					     NULL,
					     &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

/*
 * Construct a full fledged context object from all parameters
 * Report errors if any
 */
Context::Context(const cl_context_properties *properties,
		 cl_uint num_devices,
		 Device *devices,
		 void (CL_CALLBACK *notify_func)(const char *err_info, const void *private_info, size_t cb, void *user_data),
		 void *user_data)
{
  cl_int status;
  this->context = clCreateContext(properties,
				     num_devices,
				     (cl_device_id*)devices,
				     notify_func,
				     user_data,
				     &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;				     
}

/*
 * Construct a fully fledged context object using all parameters
 * from a given device type.
 * Report errors if any
 */
Context::Context(const cl_context_properties *properties,
		 cl_device_type dev_type,
		 void (CL_CALLBACK *notify_func)(const char *err_info, const void *private_info, size_t cb, void *user_data),
		 void *user_data)
{
  cl_int status;
  this->context = clCreateContextFromType(properties,
					     dev_type,
					     notify_func,
					     user_data,
					     &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

/*
 * Release the context object iff not a copy
*/
Context::~Context()
{
  if(!copy)
    clReleaseContext(this->context);
}
