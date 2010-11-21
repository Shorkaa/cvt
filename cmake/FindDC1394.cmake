FIND_PATH(LIBDC1394_INCLUDE_DIR 
	NAMES dc1394/dc1394.h
	PATHS
	${CMAKE_INCLUDE_PATH}
	/usr/local/dc1394/include	
	/usr/local/include
	/usr/include
	/opt/local/include
)

FIND_LIBRARY(LIBDC1394_LIBRARY
	NAMES dc1394
	PATHS
	${CMAKE_LIBRARY_PATH}
	/usr/local/dc1394/lib
	/usr/local/lib
	/usr/lib
	/opt/local/lib
)

IF (LIBDC1394_LIBRARY)
	SET(LIBDC1394_FOUND TRUE)
ENDIF (LIBDC1394_LIBRARY)

MARK_AS_ADVANCED(
	LIBDC1394_INCLUDE_DIR
	LIBDC1394_LIBRARY
) 
