set(SFML_TARGETS sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

cmake_minimum_required(VERSION 3.15)
project(MyNewGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(GIT_EXECUTABLE "C:/Program Files/Git/bin/git.exe")

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)
add_executable(${PROJECT_NAME} main.cpp
        ground.cpp
        base.h
        ui.h
        ui.cpp
        base.cpp
        settings.cpp
        settings.h
        tile.cpp
        tile.h
        resources.cpp
        resources.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_TARGETS})

if (WIN32 AND NOT SFML_USE_STATIC_LIBS)
    set(SFML_DLL_DESTINATION_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    set(SFML_DLL_TARGETS ${SFML_TARGETS})

    foreach(SFML_TARGET ${SFML_DLL_TARGETS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${SFML_TARGET}>
                ${SFML_DLL_DESTINATION_DIR}
                VERBATIM
                COMMENT "Copying ${SFML_TARGET} DLL to build directory"
        )
    endforeach()
endif()