cmake_minimum_required(VERSION 4.0)

project(game-of-life VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE RLIMGUI_FILES "${PROJECT_SOURCE_DIR}/build/_deps/rllmgui-src/*.cpp")
file(GLOB_RECURSE IMGUI_FILES "${PROJECT_SOURCE_DIR}/build/_deps/imgui-src/*.cpp")
set(IMGUI_BACKENDS ${PROJECT_SOURCE_DIR}/build/_deps/imgui-src/backends/imgui_impl_opengl3.cpp 
                   ${PROJECT_SOURCE_DIR}/build/_deps/imgui-src/backends/imgui_impl_glfw.cpp)

list(FILTER RLIMGUI_FILES EXCLUDE REGEX ".*/examples/.*")
list(FILTER IMGUI_FILES EXCLUDE REGEX ".*/examples/.*")
list(FILTER IMGUI_FILES EXCLUDE REGEX ".*/backends/.*")
list(FILTER IMGUI_FILES EXCLUDE REGEX ".*/misc/.*")

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  rllmgui
  GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
  GIT_TAG main 
)

FetchContent_MakeAvailable(rllmgui)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${RLIMGUI_FILES} ${IMGUI_FILES} ${IMGUI_BACKENDS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${imgui_SOURCE_DIR}
        ${rllmgui_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if (WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl GL rt X11)
endif()