SET( GLCLTOHEADER_DST "${CMAKE_BINARY_DIR}/bin/glcltoheader" )
MACRO(GLSLTOHEADER _filename )
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    GET_FILENAME_COMPONENT(_ext ${_filename} EXT )
    GET_FILENAME_COMPONENT(_path ${_filename} PATH )

	string(REGEX REPLACE "\\.(.*)" "\\1" _ext ${_ext} )

	string(REGEX REPLACE "[/.]" "_" GLSLGEN_TARGET ${_filename} )

	STRING( STRIP "${_path}" _path )
	IF( NOT "${_path}" STREQUAL "" )       
		SET(_path "${_path}/" )
    ENDIF()

	SET( GLSL_GEN_OUTPUT "${_path}${_basename}_${_ext}.h" )

    ADD_CUSTOM_COMMAND(	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${GLSL_GEN_OUTPUT}
						COMMAND ${GLCLTOHEADER_DST} 
						"${CMAKE_CURRENT_SOURCE_DIR}/${_filename}"
                        "${CMAKE_CURRENT_BINARY_DIR}/${GLSL_GEN_OUTPUT}"
						"${_basename}_${_ext}"
						DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_filename}" "glcltoheader"
    )
ENDMACRO(GLSLTOHEADER)

MACRO(CLTOHEADER _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    GET_FILENAME_COMPONENT(_path ${_filename} PATH )

	string(REGEX REPLACE "[/.]" "_" CLGEN_TARGET ${_filename} )
	
	STRING( STRIP "${_path}" _path )
	IF( NOT "${_path}" STREQUAL "" )       
		SET(_path "${_path}/" )
    ENDIF()


	SET( CL_GEN_OUTPUT "${_path}${_basename}.h" )
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${CL_GEN_OUTPUT}
		COMMAND ${GLCLTOHEADER_DST}
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
                ${CMAKE_CURRENT_BINARY_DIR}/${CL_GEN_OUTPUT}
				${_basename}
				DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_filename} glcltoheader
    )
ENDMACRO(CLTOHEADER)

