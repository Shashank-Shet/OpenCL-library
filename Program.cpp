#include<CL/Program.h>

/*
 * Construct a blank program object marked as a copy
 */
Program::Program():copy(true)
{}

/*
 * Copy a program object and mark it as a copy
 */
Program::Program(Program &obj):copy(true), program(obj.program)
{}

/*
 * Copy a program object and mark it as a copy
 */
void Program::operator=(Program &obj)
{
  this->copy = true;
  this->program = obj.program;
}

/*
 * Ability to initialize a black context object
 */
void Program::loadProgram(cl_context context, std::string filename)
{
  Program temp(context, filename);
  this->program = temp.program;
  temp.copy = true;
  this->copy = false;
}

/**
 * Read kernel code from a file given the filename and context
 * Read file line by line and create an array of pointers to 
 * each line. Run clCreateProgramFromSource req parameters.
 * Report any errors if any.
*/
Program::Program(cl_context context, std::string filename):copy(false)
{
  cl_int status;
  std::string temp;
  std::vector<std::string> input;
  std::ifstream infile(filename);
  while(std::getline(infile, temp))
    {
      input.push_back(temp);
      //      std::cout<<temp<<std::endl;
    }
  char **src = new char*[input.size()];
  for(int i=0; i<input.size(); i++)
    src[i] = (char*)(input[i].c_str());
  this->program = clCreateProgramWithSource(context, input.size(), (const char**)src, NULL, &status);
  if(status!=CL_SUCCESS)
    std::cout<<errors[status]<<std::endl;
}

/**
 * Build program using number of devices and actual devices as
 * parameters. No options or event waiting supplied.
 * Report errors if any.
 */
void Program::build(int num_devices, Device *devices)
{
  cl_int status;
  status = clBuildProgram(this->program, num_devices, (cl_device_id*)devices, NULL, NULL, NULL);
  if(status!=CL_SUCCESS)
    {
      std::cout<<errors[status]<<std::endl;
      this->debugBuild(num_devices, devices);
    }
}

/**
 * Build program using number of devices and actual devices plus
 * options. No event wait list.
 * Report errors if any.
 */
void Program::build(int num_devices, Device *devices, const char *options)
{
  cl_int status;
  status = clBuildProgram(this->program, num_devices, (cl_device_id*)devices, options, NULL, NULL);
  if(status!=CL_SUCCESS)
    {
      std::cout<<errors[status]<<std::endl;
      this->debugBuild(num_devices, devices);
    }
}

/**
 * Build program with number of devices, actual devices, build
 * options, callback notification function and any data it requires
 * Report errors if any.
 */
void Program::build(int num_devices, Device *devices, const char *options,
		    void (CL_CALLBACK *notify_func)(cl_program program, void *user_data), void *user_data)
{
  cl_int status;
  status = clBuildProgram(this->program, num_devices, (cl_device_id*)devices, options, notify_func, user_data);
  if(status!=CL_SUCCESS)
    {
      std::cout<<errors[status]<<std::endl;
      this->debugBuild(num_devices, devices);
    }  
}

/**
 * Debug last build of held program for each of the requested devices
 * and report any errors if present. Print build status, build options
 * and build log information.
 */
void Program::debugBuild(int num_devices, Device *devices)
{
  for(int i=0; i<num_devices; i++)
    {
      cl_int status;
      size_t param_len;
      int build_status;
      char *build_options, *build_logs;
      std::cout<<"Device: "<<i<<std::endl;
      status = clGetProgramBuildInfo(this->program, devices[i].getDeviceId(), CL_PROGRAM_BUILD_STATUS, 4, &build_status, NULL);
      if(status!=CL_SUCCESS)
	{
	  std::cout<<errors[status]<<std::endl;
	  continue;
	}
      clGetProgramBuildInfo(this->program, devices[i].getDeviceId(), CL_PROGRAM_BUILD_OPTIONS, 0, NULL, &param_len);
      build_options = new char[param_len];
      clGetProgramBuildInfo(this->program, devices[i].getDeviceId(), CL_PROGRAM_BUILD_OPTIONS, param_len, build_options, NULL);

      clGetProgramBuildInfo(this->program, devices[i].getDeviceId(), CL_PROGRAM_BUILD_LOG, 0, NULL, &param_len);
      build_logs = new char[param_len];
      clGetProgramBuildInfo(this->program, devices[i].getDeviceId(), CL_PROGRAM_BUILD_LOG, param_len, build_logs, NULL);

      std::cout<<"Status:  "<<build_info[build_status]<<std::endl;
      std::cout<<"Options: "<<std::endl;
      std::cout<<build_options<<std::endl;
      std::cout<<"Logs: "<<std::endl;
      std::cout<<build_logs<<std::endl;
    }
}

/**
 * Return held program object
 */
cl_program Program::getProgram()
{
  return this->program;
}

Program::~Program()
{
  if(!copy)
    clReleaseProgram(this->program);
}
