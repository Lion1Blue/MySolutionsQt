cmake_minimum_required (VERSION 3.1)

project (main)

option( MSVC_EXTENDED_ALIGNMENT "Turn on MSVC compiler definition _ENABLE_EXTENDED_ALIGNED_STORAGE " ON  )
if (MSVC_EXTENDED_ALIGNMENT)
    add_definitions(-D_ENABLE_EXTENDED_ALIGNED_STORAGE)
endif()

set (GuiLib_src 
	${PROJECT_SOURCE_DIR}/mainwindow.cpp
	${PROJECT_SOURCE_DIR}/sudokumainwindow.cpp
)

set (GuiLib_hdr 
	${PROJECT_SOURCE_DIR}/mainwindow.h
	${PROJECT_SOURCE_DIR}/sudokumainwindow.h
)

set (GuiLib_ui  
	${PROJECT_SOURCE_DIR}/mainwindow.ui
	${PROJECT_SOURCE_DIR}/sudokumainwindow.ui
)

set (GuiBin_src 
	${PROJECT_SOURCE_DIR}/main.cpp
)

qt5_wrap_cpp(GuiLib_hdr_moc ${GuiLib_hdr})
qt5_wrap_ui (GuiLib_ui_moc ${GuiLib_ui})

include_directories (
	${PROJECT_SOURCE_DIR}
	${PROJECT_BINARY_DIR}
	../sudoku
)

add_library (GUI
	${GuiLib_hdr}
    ${GuiLib_src}
    ${GuiLib_hdr_moc}
    ${GuiLib_ui_moc}
)

target_link_libraries (
	GUI 
	Qt5::Widgets
	sudoku
)

add_executable(main
	${GuiBin_src}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    DEBUG_POSTFIX "d"
    RELEASE_POSTFIX ""
    RELWITHDEBINFO_POSTFIX ""
	FOLDER "${FOLDER_NAME}"
)

target_link_libraries (main GUI)