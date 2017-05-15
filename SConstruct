import os

eco_train_gpu = 'eco_train_gpu.cpp'

includes = ['include', '/usr/local/include/opencv2', '/usr/local/include/opencv','/usr/local/include/flycapture/']

#cxx_flags = "-Wall -g -fno-inline -fopenmp"
#cxx_flags = "-Wall -g -fno-inline"
cxx_flags = "-Wall -O3 -fopenmp -std=c++11"
link_flags = "-fopenmp"

env = Environment(CPPPATH=includes, CXXFLAGS=cxx_flags, LINKFLAGS=link_flags, 
		LIBS=boost_libs + opencv_libs ,
		LIBPATH=['/usr/local/lib'],
		LD_LIBRARY_PATH=['/usr/local/lib'])

env.Program('bin/eco_train_gpu', eco_train_gpu)
