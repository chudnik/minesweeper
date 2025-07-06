function(download_sfml)
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/include/SFML/Graphics.hpp")
        message(STATUS "Downloading SFML...")

        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs")

        if (WIN32)
            set(SFML_URL "https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc14-32-bit.zip")
        elseif (APPLE)
            set(SFML_URL "https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz")
        else ()
            set(SFML_URL "https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz")
        endif ()

        file(DOWNLOAD
                ${SFML_URL}
                "${CMAKE_CURRENT_BINARY_DIR}/sfml_temp.zip"
                SHOW_PROGRESS
        )

        execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_BINARY_DIR}/sfml_temp.zip"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs"
        )

        file(GLOB SFML_EXTRACTED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-*")
        file(RENAME ${SFML_EXTRACTED_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML")

        message(STATUS "SFML successfully downloaded")
    endif ()
endfunction()