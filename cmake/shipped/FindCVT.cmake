SET( CMAKE_SYSTEM_INCLUDE_PATH /usr/include/nvidia-current ${CMAKE_SYSTEM_INCLUDE_PATH} )

FIND_PACKAGE(OpenCL REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Eigen3 REQUIRED)

INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${OpenCL_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${Eigen3_INCLUDE_DIRS} )

FIND_PATH( CVT_INCLUDE_DIR 
	NAMES cvt/gfx/Image.h
	PATHS
	${CMAKE_INCLUDE_PATH}
	/usr/include
	/usr/local/include
)

FIND_LIBRARY( CVT_LIBRARY
	NAMES cvt
	PATHS
	${CMAKE_LIBRARY_PATH}
	/usr/lib
	/usr/local/lib
)

IF( CVT_LIBRARY )
	SET( CVT_FOUND TRUE )
ENDIF ( CVT_LIBRARY )

SET( CVT_LIBRARIES 
	"${CVT_LIBRARY}"
	"${OPENGL_LIBRARIES}"
	"${OpenCL_LIBRARIES}"
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ADD_DEFINITIONS(-DPOSIX -DAPPLE -D__APPLE__)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

MARK_AS_ADVANCED(
	CVT_INCLUDE_DIR
	CVT_LIBRARY
	CVT_LIBRARIES
)
