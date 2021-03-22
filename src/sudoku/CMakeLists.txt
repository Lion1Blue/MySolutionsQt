cmake_minimum_required(VERSION 3.1)

project(sudoku)

set(HEADERS
	${PROJECT_NAME}.h
	ISudokuMainWindow.h
)

set(SOURCES
	${PROJECT_NAME}.cpp
)

add_library(${PROJECT_NAME}
	${HEADERS}
	${SOURCES}
)

target_link_libraries (
	${PROJECT_NAME}
	Qt5::Core
	Qt5::Widgets
)

include_directories(
	${PROJECT_SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    DEBUG_POSTFIX "d"
    RELEASE_POSTFIX ""
    RELWITHDEBINFO_POSTFIX ""
	FOLDER "${FOLDER_NAME}"
)

target_include_directories(${PROJECT_NAME} PUBLIC
)
