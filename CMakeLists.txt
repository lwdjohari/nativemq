cmake_minimum_required(VERSION 3.5)

# change this project name to your project.
project(nativemq CXX)

message( "\n${PROJECT_NAME} Lib")
message( "-----------------------------")
message(STATUS "${PROJECT_NAME} LIB DIR:${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/nativemq/*.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/nativemq/*.cc      
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/nativemq/*.s
# )

#cli11
add_subdirectory(deps/cli11 build-cli11)

#yaml-cpp
add_subdirectory(deps/yaml-cpp build-yaml)

#abseil-cpp
add_subdirectory(deps/abseil build-abseil)

#nvcore
add_subdirectory(deps/nvcore build-nvcore)

#nvlog
#add_subdirectory(deps/nvlog build-nvlog)


#nativemq lib

# Manually defined sources
set(SOURCES
  src/nativemq/global_macro.h
  src/nativemq/declare.h
  src/nativemq/utils/yaml/yaml_helper.h
  src/nativemq/config/config_def.h
  src/nativemq/config/config_loader.h
  src/nativemq/config/config_loader.cc
)

configure_file(
  ${CMAKE_SOURCE_DIR}/config/nativemq.dev.yaml
  ${CMAKE_BINARY_DIR}/config/nativemq.dev.yaml
  COPYONLY
)

add_library(nativemq ${SOURCES})
target_link_libraries(nativemq 
    PUBLIC 
        # ${CMAKE_CURRENT_SOURCE_DIR}/deps/boost
        yaml-cpp
)

# target_compile_options(nativemq
#     PRIVATE
#         -isystem ${CMAKE_CURRENT_SOURCE_DIR}/deps/boost
# )

target_compile_definitions(nativemq 
    PRIVATE
        BOOST_ASIO_NO_DEPRECATED
        BOOST_ERROR_CODE_HEADER_ONLY
)

target_include_directories(nativemq
    PUBLIC
        src/
)

target_compile_features(nativemq 
    PUBLIC 
        cxx_std_17)

# nativemq-broker binary
# front facing MQTT Gateway service
add_executable(nativemq-broker src/natmq_gateway/main.cc)
target_link_libraries(nativemq-broker
    PRIVATE
    CLI11::CLI11
    nativemq
    )
target_compile_features(nativemq-broker PUBLIC cxx_std_17)

# nativemq-vmbox
# mailbox and message router service
# add_executable(nativemq-vmbox src/natmq_broker/main.cc)
# target_link_libraries(nativemq-vmbox 
#     nativemq
#     )
# target_compile_features(nativemq-vmbox PUBLIC cxx_std_17)

message(STATUS "${PROJECT_NAME} Configuration Done!\n")
