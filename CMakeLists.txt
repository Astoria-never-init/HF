cmake_minimum_required(VERSION 3.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(HF)

#Render_system
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)
include_directories(
${LIBRARY_DIR}/include/glad/include
${LIBRARY_DIR}/include/glfw/include
#${LIBRARY_DIR}/include/glm
#${LIBRARY_DIR}/include/imgui
)
set(GLAD ${LIBRARY_DIR}/include/glad/src/glad.c )


file(GLOB BUFFERS ${CMAKE_SOURCE_DIR}/src/graphics/BUFFERS/*)

source_group("BUFFERS" FILES ${BUFFERS})
add_library(render STATIC ${BUFFERS} ${GLAD})


#debug

include_directories(${LIBRARY_DIR}/include)
link_directories(${LIBRARY_DIR}/_win/glfw/lib-32)


# 
add_executable(debug ${CMAKE_SOURCE_DIR}/src/main.cpp ${GLAD})

target_link_libraries(debug glfw3)