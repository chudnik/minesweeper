cmake_minimum_required(VERSION 3.15)
project(Minesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/DownloadSFML.cmake)
download_sfml()

set(SFML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/include")
set(SFML_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/lib")

add_library(sfml-graphics SHARED IMPORTED)
add_library(sfml-window SHARED IMPORTED)
add_library(sfml-system SHARED IMPORTED)

if (WIN32)
    set_target_properties(sfml-graphics PROPERTIES
            IMPORTED_IMPLIB "${SFML_LIBRARY_DIR}/sfml-graphics.lib"
            IMPORTED_LOCATION "${SFML_LIBRARY_DIR}/../bin/sfml-graphics-2.dll"
    )
    set_target_properties(sfml-window PROPERTIES
            IMPORTED_IMPLIB "${SFML_LIBRARY_DIR}/sfml-window.lib"
            IMPORTED_LOCATION "${SFML_LIBRARY_DIR}/../bin/sfml-window-2.dll"
    )
    set_target_properties(sfml-system PROPERTIES
            IMPORTED_IMPLIB "${SFML_LIBRARY_DIR}/sfml-system.lib"
            IMPORTED_LOCATION "${SFML_LIBRARY_DIR}/../bin/sfml-system-2.dll"
    )
else ()
    set_target_properties(sfml-graphics PROPERTIES
            IMPORTED_LOCATION "${SFML_LIBRARY_DIR}/libsfml-graphics.so.2.5"
    )
    set_target_properties(sfml-window PROPERTIES
            IMPORTED_LOCATION "${SFML_LIBRARY_DIR}/libsfml-window.so.2.5"
    )
    set_target_properties(sfml-system PROPERTIES
            IMPORTED_LOCATION "${SFML_LIBRARY_DIR}/libsfml-system.so.2.5"
    )
endif ()

add_executable(minesweeper
        src/main.cpp
        src/core/Board.cpp
        src/ui/Renderer.cpp
        src/ui/InputHandler.cpp
)

if (WIN32)
    add_custom_command(TARGET minesweeper POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_LIBRARY_DIR}/../bin/sfml-graphics-2.dll"
            "${SFML_LIBRARY_DIR}/../bin/sfml-window-2.dll"
            "${SFML_LIBRARY_DIR}/../bin/sfml-system-2.dll"
            $<TARGET_FILE_DIR:minesweeper>
            COMMENT "Copying SFML DLLs to output directory"
    )
endif ()

target_include_directories(minesweeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SFML_INCLUDE_DIR}
)

target_link_libraries(minesweeper PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})