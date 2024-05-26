# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("calculator")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add compile options
add_compile_options(
        -w
        -s
        -Wno-error=format-security
        -fvisibility=hidden
        -fpermissive
        -fexceptions
        -Werror
        -Wno-error=c++11-narrowing
        -Wall
)

# Add link options
add_link_options(
        -Wl,--gc-sections
        -Wl,--strip-all
        -llog
        -landroid
        -lEGL
        -lGLESv2
)

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/ImGui
        ${CMAKE_SOURCE_DIR}/ImGui/backends
)

# Source files
set(SOURCE_FILES
        native-lib.cpp
        ImGui/imgui.cpp
        ImGui/imgui_draw.cpp
        ImGui/imgui_widgets.cpp
        ImGui/imgui_tables.cpp
        ImGui/backends/imgui_impl_opengl3.cpp
        ImGui/backends/imgui_impl_android.cpp
)

# Add the shared library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
        log
        android
        EGL
        GLESv2
)