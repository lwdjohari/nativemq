cmake_minimum_required(VERSION 3.5)

# change this project name to your project.
project(nativemq CXX)

message( "\n${PROJECT_NAME} Lib")
message( "-----------------------------")
message(STATUS "${PROJECT_NAME} LIB DIR:${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nativemq/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nativemq/*.cc      
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nativemq/*.s
)

#nvcore
add_subdirectory(deps/nvcore build-nvcore)

#asio
# Add ASIO as a standalone library
add_library(asio INTERFACE)
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps/asio/asio/include)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        nvcore
        asio
)
target_include_directories("${PROJECT_NAME}"
    PUBLIC
        src/
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


add_executable(${PROJECT_NAME}-server src/main.cc)
target_link_libraries(${PROJECT_NAME}-server 
    ${PROJECT_NAME}
    )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

message(STATUS "${PROJECT_NAME} Configuration Done!\n")