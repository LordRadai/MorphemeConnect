cmake_minimum_required(VERSION 3.10)
project(cfr VERSION 0.0.1 DESCRIPTION "cfr 001")

include(GNUInstallDirs)

if(WIN32)
	add_compile_definitions(_WIN32)
endif()

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIRS})

#copy the filelists needed for dvdbnds
file(COPY "res/" DESTINATION "release/res/")

include_directories(cmem)

set(SOURCES
	"util/files/files.cpp"
	"util/strings/strings.cpp"
	"util/hashing/hash_util.cpp"
	"util/filetypes.cpp"
	"util/compat/compat.cpp"
	"util/compression/zlib_inf.cpp"
	"binders/bdf/bdf3.cpp"
	"binders/bhd/bhd5_1.cpp"
	"binders/bnd/bnd3.cpp"
	"binders/dcx/dcx.cpp"
	"formats/flver/flver2.cpp"
	"formats/paramdef/paramdef.cpp"
)

add_library(cfr STATIC ${SOURCES} "cfr.hpp")

target_link_libraries(cfr cmem ZLIB::ZLIB)

target_include_directories(cfr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})