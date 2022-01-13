CXX = g++
CC = gcc

SRC_FILES = CLInfo.cpp Environment.cpp Platform.cpp Device.cpp Enumerated_Types.cpp Context.cpp Buffer.cpp Program.cpp Kernel.cpp CommandQueue.cpp

SHARED_OBJECT_NAME = libmyOpenCLapi.so

# LIBRARIES = -L/opt/intel/opencl -lOpenCL

LIBRARIES = 

OBJECTS = $(patsubst %, %.o, $(basename $(SRC_FILES)))

compile_so:$(OBJECTS)
	g++ $(OBJECTS) -shared -o $(SHARED_OBJECT_NAME) $(LIBRARIES)

%.o:%.cpp
	$(CXX) -fPIC -c $< $(LIBRARIES)

%.o:%.c
	$(CC) -fPIC -c $< $(LIBRARIES)

clean:
	rm *.o

