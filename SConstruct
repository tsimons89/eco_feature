import os

boost_libs = Split('boost_filesystem boost_program_options boost_system boost_regex')

opencv_libs = Split('opencv_core opencv_highgui opencv_imgproc opencv_objdetect opencv_ml opencv_imgcodecs opencv_videoio')

cuda_opencv_libs = Split('''opencv_cudaarithm opencv_cudabgsegm opencv_cudacodec opencv_cudafeatures2d opencv_cudafilters 
	opencv_cudaimgproc opencv_cudalegacy opencv_cudaobjdetect opencv_cudaoptflow opencv_cudastereo opencv_cudawarping''')

flycapture_libs = Split('flycapture flycapturegui')

includes = Split('''
	#core/include 
	#camera/include
	#demo/include
	/usr/local/include/opencv2 
	/usr/local/include/opencv 
	/usr/include/flycapture/ 
	/usr/local/cuda-8.0/include/
	''')

cxx_flags = "-Wall -O3 -fopenmp -std=c++11"
link_flags = "-fopenmp"
# cxx_flags = "-pg -std=c++11"
# link_flags = "-pg"

env = Environment(CPPPATH=includes, CXXFLAGS=cxx_flags, LINKFLAGS=link_flags, 
		LIBS=boost_libs + opencv_libs + cuda_opencv_libs + flycapture_libs,
		LIBPATH=['/usr/local/lib'],
		LD_LIBRARY_PATH=['/usr/local/lib'])

objs = []
for subdir in ['core','camera','demo']:
	o = SConscript('%s/SConscript' % subdir,exports=['env','objs'],variant_dir='#%s/core' % subdir, duplicate=0)
	objs.append(o)
# SConscript('core/SConscript',exports='env',variant_dir='#build/core', duplicate=0)
# SConscript('camera/SConscript',exports='env',variant_dir='#build/camera', duplicate=0)
# SConscript('demo/SConscript',exports='env',variant_dir='#build/demo', duplicate=0)

