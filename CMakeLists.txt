cmake_minimum_required(VERSION 3.0)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(HF)



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(Threads REQUIRED)
elseif()
    set(CMAKE_GENERATOR_PLATFORM "x64")
endif()



#set libarys
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)
include_directories(
${LIBRARY_DIR}/include/glad/include
${LIBRARY_DIR}/include/glfw/include
#${LIBRARY_DIR}/include/glm
#${LIBRARY_DIR}/include/imgui
)

set(GLAD ${LIBRARY_DIR}/include/glad/src/glad.c )

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	link_directories(${LIBRARY_DIR}/_lin/glfw/lib)
		
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	link_directories(${LIBRARY_DIR}/_win/glfw/lib)
else()
    message(FATAL_ERROR "Uncorrect OS")
	
endif()



#set src
file(GLOB BUFFERS ${CMAKE_SOURCE_DIR}/src/graphics/BUFFERS/*)
source_group("BUFFERS" FILES ${BUFFERS})



#add lib project
add_library(render STATIC ${BUFFERS} ${GLAD})
#debug
add_executable(debug ${CMAKE_SOURCE_DIR}/src/main.cpp ${GLAD})



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(debug dl Threads::Threads)
    target_link_libraries(debug libglfw3.a)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(debug glfw3)
endif()



if(MSVC)
    set_target_properties(debug PROPERTIES COMPILE_OPTIONS "/arch:AVX")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(debug PROPERTIES COMPILE_FLAGS "-m64 -march=native")
endif()