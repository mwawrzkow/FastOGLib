cmake_minimum_required(VERSION 3.7.2)
project(RPG_ENGINE)
include(ExternalProject)
set(A_Engine_debug TRUE)
add_subdirectory(Engine)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# ExternalProject_Add(Logger 
#     GIT_REPOSITORY https://github.com/mwawrzkow/LoggerCpp
#     GIT_TAG main
# )

# include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
# link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)