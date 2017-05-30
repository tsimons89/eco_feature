import os

eco_src = Split('''
	src/Filter.cpp 
	src/Genome.cpp 
	src/Creature.cpp 
	src/probability.cpp
	src/Population.cpp
	src/Data_set.cpp
	src/Options.cpp
	src/Adaboost_model.cpp
	''')

boost_libs = Split('''boost_filesystem boost_program_options boost_system boost_regex''')

opencv_libs = Split('''opencv_core opencv_highgui opencv_imgproc opencv_objdetect opencv_ml opencv_imgcodecs opencv_videoio''')

cuda_opencv_libs = Split('''opencv_cudaarithm opencv_cudabgsegm opencv_cudacodec opencv_cudafeatures2d opencv_cudafilters 
	opencv_cudaimgproc opencv_cudalegacy opencv_cudaobjdetect opencv_cudaoptflow opencv_cudastereo opencv_cudawarping''')



includes = ['include', '/usr/local/include/opencv2', '/usr/local/include/opencv','/usr/local/include/flycapture/','/usr/local/cuda-8.0/include/']

#cxx_flags = "-Wall -g -fno-inline -fopenmp"
#cxx_flags = "-Wall -g -fno-inline"
cxx_flags = "-Wall -O3 -fopenmp -std=c++11"
link_flags = "-fopenmp"

env = Environment(CPPPATH=includes, CXXFLAGS=cxx_flags, LINKFLAGS=link_flags, 
		LIBS=boost_libs + opencv_libs + cuda_opencv_libs,
		LIBPATH=['/usr/local/lib'],
		LD_LIBRARY_PATH=['/usr/local/lib'])

env.Program('bin/eco_train', ['src/eco_train.cpp'] + eco_src)
env.Program('bin/eco_test', ['src/eco_test.cpp'] + eco_src)
env.Program('bin/eco_single_predict', ['src/eco_single_predict.cpp'] + eco_src)
env.Program('bin/test', ['src/test_main.cpp'] + eco_src)
