# Lists of directories with source files:
#  See "DeclareMRPTLib.cmake" for explanations
# -------------------------------------------------
LIST(APPEND maps_EXTRA_SRCS			"${MRPT_SOURCE_DIR}/libs/maps/src/maps/*.cpp" "${MRPT_SOURCE_DIR}/libs/maps/include/mrpt/maps/*.h" "${MRPT_SOURCE_DIR}/libs/maps/include/mrpt/slam/*.h")
LIST(APPEND maps_EXTRA_SRCS_NAME 	"maps" "maps" "back-compat-hdrs")

LIST(APPEND maps_EXTRA_SRCS			"${MRPT_SOURCE_DIR}/libs/maps/src/opengl/*.cpp" "${MRPT_SOURCE_DIR}/libs/maps/include/mrpt/opengl/*.h")
LIST(APPEND maps_EXTRA_SRCS_NAME 	"opengl" "opengl")

IF(CMAKE_MRPT_HAS_LIBLAS)
	LINK_DIRECTORIES(${LAS_LINK_DIRS})
	INCLUDE_DIRECTORIES(${LAS_INCLUDE_DIRS})
ENDIF()

#---------------------------------------------
# Macro declared in "DeclareMRPTLib.cmake":
#---------------------------------------------
define_mrpt_lib(
	# Lib name
	maps
	# Dependencies:
	mrpt-obs
	mrpt-graphs
	# Deps of deps:
	mrpt-opengl
	mrpt-base
	)

IF(BUILD_mrpt-maps)
	IF (CMAKE_MRPT_HAS_PCL)
		target_link_libraries(mrpt-maps ${PCL_LIBRARIES})
	ENDIF()

	IF(CMAKE_MRPT_HAS_LIBLAS)
		target_link_libraries(mrpt-maps ${LAS_LIBS})
	ENDIF()

	IF (CMAKE_MRPT_HAS_VTK)
        INCLUDE(${VTK_USE_FILE})
		target_link_libraries(mrpt-maps ${VTK_LIBRARIES})
	ENDIF()

	IF (CMAKE_MRPT_HAS_OCTOMAP)
		if (NOT "${OCTOMAP_LIBRARY_DIRS}" STREQUAL "")
			LINK_DIRECTORIES("${OCTOMAP_LIBRARY_DIRS}")
		endif()
		IF(TARGET "EP_octomap")
			ADD_DEPENDENCIES(mrpt-maps EP_octomap)
		ENDIF()
		target_link_libraries(mrpt-maps ${OCTOMAP_LIBRARIES})
	ENDIF()

ENDIF()
