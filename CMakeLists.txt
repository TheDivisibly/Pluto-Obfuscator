cmake_minimum_required(VERSION 3.21)

project(Pluto-Obfuscator)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /std:c++latest")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /std:c++latest")

aux_source_directory(./src src_1)
set(srcs ${src_1})

add_library(Pluto-Obfuscator SHARED ${srcs})

# Our includes path
include_directories("./include")

# includes at build dir of llvm
include_directories("../build/include")

# includes of llvm
include_directories("../llvm/include")

file(GLOB LIBS "../build/lib/LLVM*.lib")

target_link_libraries(Pluto-Obfuscator PUBLIC ${LIBS})
