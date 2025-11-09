cmake_minimum_required(VERSION 3.16)
project(STLVisualizerProject_Portable)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_NAME "STLViewer")

file(GLOB_RECURSE SRC
    src/*.cpp
    vendor/imgui/*.cpp
    vendor/glad.c
)

file(GLOB_RECURSE HDR
    src/*.h
    vendor/imgui/*.h
    vendor/include/glad/*.h
)

add_executable(${EXECUTABLE_NAME} ${SRC} ${HDR})

target_include_directories(${EXECUTABLE_NAME} PRIVATE
    src
    src/Core
    src/File
    src/Input
    src/Rendering
    src/UI
    vendor/imgui
    vendor/include
)

target_link_directories(${EXECUTABLE_NAME} PRIVATE vendor/lib)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw3)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    opengl32
    gdi32
    user32
    shell32
)

if(WIN32)
    set(APP_ICON_RC "${CMAKE_SOURCE_DIR}/assets/icons/icon.rc")
    if(EXISTS ${APP_ICON_RC})
        target_sources(${EXECUTABLE_NAME} PRIVATE ${APP_ICON_RC})
    endif()
endif()

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets
)
