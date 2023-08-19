cmake_minimum_required(VERSION 3.0)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(HF)

add_compile_options(-std=c++11)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(Threads REQUIRED)
elseif()
    set(CMAKE_GENERATOR_PLATFORM "x64")
endif()


#set libarys
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)



include_directories(

#${CMAKE_SOURCE_DIR}/src/graphics
${LIBRARY_DIR}/include/glm
#${LIBRARY_DIR}/include/imgui
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	link_directories(${LIBRARY_DIR}/_lin/glfw/lib)
		
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	link_directories(${LIBRARY_DIR}/_win/glfw/lib)
else()
    message(FATAL_ERROR "Uncorrect OS")
	
endif()




#add render lib
file(GLOB RENDER_HEADERS ${CMAKE_SOURCE_DIR}/src/graphics/headers/*.h)
source_group("headers" FILES ${RENDER_HEADERS})

file(GLOB RENDER_BUFFERS ${CMAKE_SOURCE_DIR}/src/graphics/BUFFERS/*.cpp)
source_group("BUFFERS" FILES ${RENDER_BUFFERS})

file(GLOB RENDER_SHADERS ${CMAKE_SOURCE_DIR}/src/graphics/SHADERS/*.cpp)
source_group("SHADERS" FILES ${RENDER_SHADERS})

file(GLOB RENDER_CAMERA ${CMAKE_SOURCE_DIR}/src/graphics/CAMERA/*.cpp)
source_group("CAMERA" FILES ${RENDER_CAMERA})

file(GLOB RENDER_TEXTURE ${CMAKE_SOURCE_DIR}/src/graphics/TEXTURE/*.cpp)
source_group("TEXTURE" FILES ${RENDER_TEXTURE})


add_library(render STATIC ${RENDER_HEADERS} ${RENDER_BUFFERS} ${RENDER_SHADERS} ${RENDER_CAMERA} ${RENDER_TEXTURE})


target_include_directories(render PRIVATE 
${CMAKE_SOURCE_DIR}/src/graphics/headers
${LIBRARY_DIR}/include/glad/include)



#add objects lib
file(GLOB API_HEADERS ${CMAKE_SOURCE_DIR}/src/api/headers/*.h)
source_group("headers" FILES ${API_HEADERS})

file(GLOB API_CAMERA ${CMAKE_SOURCE_DIR}/src/api/CAMERA/*.cpp)
source_group("CAMERA" FILES ${API_CAMERA})

file(GLOB API_STATIC_MESH ${CMAKE_SOURCE_DIR}/src/api/STATIC_MESH/*.cpp)
source_group("STATIC_MESH" FILES ${API_STATIC_MESH})

file(GLOB API_RENDER_SECTION ${CMAKE_SOURCE_DIR}/src/api/RENDER_SECTION/*.cpp)
source_group("RENDER_SECTION" FILES ${API_RENDER_SECTION})

file(GLOB API_SCENE_CULLING ${CMAKE_SOURCE_DIR}/src/api/SCENE_CULLING/*.cpp)
source_group("SCENE_CULLING" FILES ${API_SCENE_CULLING})

add_library(api STATIC ${API_HEADERS} ${API_CAMERA} ${API_STATIC_MESH} ${API_RENDER_SECTION} ${API_SCENE_CULLING})

target_include_directories(api PRIVATE 
${CMAKE_SOURCE_DIR}/src/graphics/headers 
${CMAKE_SOURCE_DIR}/src/api/headers
${LIBRARY_DIR}/include/glad/include
)
target_link_libraries(api PRIVATE render)



#debug
set(GLAD ${LIBRARY_DIR}/include/glad/src/glad.c )
set(STB_IMAGE ${CMAKE_SOURCE_DIR}/src/stb_image.h )


add_executable(debug ${CMAKE_SOURCE_DIR}/src/main.cpp ${GLAD} ${STB_IMAGE})


target_include_directories(debug PRIVATE 
${CMAKE_SOURCE_DIR}/src/graphics/headers 
${CMAKE_SOURCE_DIR}/src/api/headers
${LIBRARY_DIR}/include/glad/include
${LIBRARY_DIR}/include/glfw/include
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(debug PRIVATE render dl Threads::Threads libglfw3.a)
    #target_link_libraries(debug PRIVATE render)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(debug PRIVATE render api glfw3)
endif()





if(MSVC)
    set_target_properties(debug PROPERTIES COMPILE_OPTIONS "/arch:AVX")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(debug PROPERTIES COMPILE_FLAGS "-m64 -march=native")
endif()
