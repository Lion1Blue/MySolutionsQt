# define what to do on different platforms
if(WIN32)
	message("OS: Windows")
    cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
	set(PLATTFORM_INSTALL_DIR "win")
	
elseif(UNIX)
	message("OS:UNIX")
    cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
	set(PLATTFORM_INSTALL_DIR "linux")
endif()

# solution name
project(MySolutions)

# set the paths first
include(CMakeListsSettings_$ENV{USERNAME}.txt OPTIONAL RESULT_VARIABLE LOCAL_PATH_SETTING_OK)
if(LOCAL_PATH_SETTING_OK)
    message("using local path settings of user $ENV{USERNAME}")
else(LOCAL_PATH_SETTING_OK)
    message("WARNING: using default path settings. please create your own CMakeListsSettings_USERNAME.txt")
#    include(PathsForCmake.txt)
endif()

#Qt5
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
if(Qt5_FOUND)
 message("-- Found Qt5")
else(Qt5_FOUND)
 message(FATAL_ERROR "-- Not found Qt5")
endif(Qt5_FOUND)

#Qt5Widgets
find_package(Qt5Widgets REQUIRED)
if(Qt5Widgets_FOUND)
 message("-- Found Qt5Widgets")
else(Qt5Widgets_FOUND)
 message(FATAL_ERROR "-- Not found Qt5Widgets")
endif(Qt5Widgets_FOUND)

# used libraries
include_directories(
	${CMAKE_SOURCE_DIR}/src
)

# linked directories
#link_directories(
#	Qt5::Widgets
#)

# enable install() routines
macro(a_post_build_install NAME)
  if(MSVC_IDE)
    add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_CONFIG_NAME=${CMAKE_CFG_INTDIR} -P cmake_install.cmake)
  endif(MSVC_IDE)
endmacro(a_post_build_install NAME)

#enable local debugging setting (debugger command + arguments + working directory) via userfile
macro(load_DebuggingTemplate NAME SUFFIX FILE_DIR)
    # setting default VS_DEBUGGER_COMMAND
    set_target_properties(${NAME} PROPERTIES
	    VS_DEBUGGER_COMMAND "${CMAKE_INSTALL_PREFIX}/$<$<CONFIG:Debug>:Debug/>$<$<CONFIG:Release>:Release/>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo/>$<TARGET_FILE_NAME:${NAME}>"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/$<$<CONFIG:Debug>:Debug/>$<$<CONFIG:Release>:Release/>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo/>"
    )

    # read DebuggingTemplate config from local user to overwrite debugger command + arguments + working directory
    SET(USER_NAME $ENV{USERNAME} CACHE STRING UserName)
    SET(USER_FILE ${FILE_DIR}/${PROJECT_NAME}.vcxproj.user)
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/DebuggingTemplate.${USER_NAME}.user ${USER_FILE} @ONLY)
endmacro(load_DebuggingTemplate NAME SUFFIX FILE_DIR)

# add source directories
add_subdirectory(src/GUI)
add_subdirectory(src/sudoku)


