cmake_minimum_required(VERSION 3.7.2)

project(RPG_ENGINE)
add_subdirectory(Core)

file(COPY "shaders/" DESTINATION "Core/")
file(COPY "exampleimgs/" DESTINATION "Core/")

