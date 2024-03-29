cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(CG1-raytracer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited config" FORCE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSIGNMENT_LIBRARIES)

find_package(PNG QUIET)
if (PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    add_definitions(${PNG_DEFINITIONS})
    set(ASSIGNMENT_LIBRARIES ${ASSIGNMENT_LIBRARIES} ${PNG_LIBRARIES})
elseif(WIN32 AND MSVC)
    add_definitions(-DGDIPLUS_SUPPORT)
    set(ASSIGNMENT_LIBRARIES ${ASSIGNMENT_LIBRARIES} gdiplus)
else()
    find_package(PNG)
    message(FATAL_ERROR "libpng-dev is required to build the CG1-raytracer.\nPlease install libpng-dev.")
endif ()


find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(ALL_ASSIGNMENT_SOURCES)

file(GLOB ASSIGNMENT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/assignment-*.cmake")
foreach(f ${ASSIGNMENT_FILES})
    get_filename_component(_fname ${f} NAME_WE)
    message(STATUS "Found files of ${_fname}")
    include(${f})
    foreach(_s ${ASSIGNMENT_SOURCES})
        message(STATUS " - ${_s}")
    endforeach()
    list(APPEND ALL_ASSIGNMENT_SOURCES ${ASSIGNMENT_SOURCES})
endforeach()

add_executable(cgray ${ALL_ASSIGNMENT_SOURCES} main/main.cpp)
target_link_libraries(cgray ${ASSIGNMENT_LIBRARIES})
