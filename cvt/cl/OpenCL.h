#ifndef CVT_OPENCL_H
#define CVT_OPENCL_H

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

namespace cvt {
	class ApplicationX11;
	class CLContext;
	class CLCommandQueue;
	class CLDevice;

	class CL {
		friend class ApplicationX11;
		public:
			static CLContext* defaultContext() { return _ctx; }
			static CLCommandQueue* defaultQueue() { return _queue; }
			static CLDevice* defaultDevice() { return _device; }
			static bool	defaultGLsharing() { return _glsharing; }
		private:
			static void init( cl_device_id id, cl_context_properties* props );

			// default context, device and queue
			static bool			   _glsharing = false;
			static CLContext*	   _ctx = NULL;
			static CLDevice*	   _device = NULL;
			static CLCommandQueue* _queue = NULL;
	};
}

#endif
