cmake_minimum_required(VERSION 3.14)
include(FetchContent)


FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_Declare(glew 
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        )
FetchContent_Declare(
                stb
                GIT_REPOSITORY https://github.com/nothings/stb.git
                GIT_TAG master
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                )
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glew)
FetchContent_MakeAvailable(stb)


add_compile_options(-Wall)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall)
add_compile_options(-Wextra)
# add_compile_options(-Werror)
# add_compile_options(-Wpedantic)
add_executable(main main.cpp)

if(WIN32)
        add_compile_definitions(GLEW_STATIC)
endif()
add_library(gl_Core 
        core/base/vertexHandler.cpp 
        core/base/Primitive.cpp 
        core/WindowProperties.cpp 
        core/primitives/Square.cpp 
        core/primitives/Rectanagle.cpp 

        # core/primitives/PrimitivesManager.cpp
        # core/primitives/Lights.cpp
        # core/primitives/Light/DirectLight.cpp
        # core/primitives/Light/SphericalLight.cpp
        # core/primitives/Light/GlobalLight.cpp #TODO: add when starts working
        core/primitives/Line.cpp
        core/OpenGLArrays/ArrayHandler.cpp 
        core/base/Texture.cpp
        core/base/OpenGLStart.cpp
)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

target_include_directories(gl_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include )
target_include_directories(gl_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include )


set(GL_DEF glfw 
libglew_static)
 
set(engineLibs gl_Core)
target_link_libraries(gl_Core PRIVATE ${GL_DEF})
target_include_directories(gl_Core PUBLIC ${CMAKE_BINARY_DIR}/_deps/stb-src)
target_include_directories(gl_Core PUBLIC ${CMAKE_BINARY_DIR}/_deps/glew-src/include)
target_include_directories(gl_Core PUBLIC ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
# if(A_Engine_debug)
target_include_directories(main PUBLIC ${CMAKE_BINARY_DIR}/_deps/glew-src/include)
target_include_directories(main PUBLIC ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_link_libraries(main gl_Core)
# endif()

