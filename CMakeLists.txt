# run these commands from root of webrt directory to build project
# source "emsdk/emsdk_env.sh"
# emcmake cmake -B build
# cmake --build build

cmake_minimum_required(VERSION 4.0)
project(webrt CXX)

if(NOT CMAKE_CXX_COMPILER MATCHES "em\\+\\+")
  message(WARNING "CMAKE_CXX_COMPILER is not em++, please run: emcmake cmake -B build")
endif()

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(index ${SOURCES} ${HEADERS})
set_target_properties(index PROPERTIES
    OUTPUT_NAME "index"
    SUFFIX ".html"
)
set_property(TARGET index PROPERTY CXX_STANDARD 17)

if(DEFINED ENV{EMSDK})
    set(EMSCRIPTEN_ROOT "$ENV{EMSDK}/upstream/emscripten")
else()
    message(WARNING "EMSDK enviornment variable not set!\nset with 'source \"emsdk/emsdk_env.sh\"'")
endif()

find_package(glm CONFIG REQUIRED)
target_link_libraries(index PRIVATE glm::glm)

target_include_directories(index PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
    ${EMSCRIPTEN_ROOT}/cache/sysroot/include
)

target_compile_options(index PRIVATE
    -O3
    #-msimd128
)
target_link_options(index PRIVATE
    --03
    #--msimd128

    --shell-file=${CMAKE_SOURCE_DIR}/shell_minimal.html
    -sMAX_WEBGL_VERSION=2
    -I./lib
)