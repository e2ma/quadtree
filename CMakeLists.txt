CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(euclidean-distance-transform)

FIND_PACKAGE(OpenGL)

# Default to release build
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

IF(MSVC)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  SET(CompilerFlags
          CMAKE_CXX_FLAGS
          CMAKE_CXX_FLAGS_DEBUG
          CMAKE_CXX_FLAGS_RELEASE
          CMAKE_C_FLAGS
          CMAKE_C_FLAGS_DEBUG
          CMAKE_C_FLAGS_RELEASE)
  FOREACH(CompilerFlag ${CompilerFlags})
    STRING(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  ENDFOREACH()
  MESSAGE(STATUS "CXX flags (release): ${CMAKE_CXX_FLAGS_RELEASE}")
  MESSAGE(STATUS "CXX flags (debug): ${CMAKE_CXX_FLAGS_DEBUG}")
ENDIF()

# Project Compiler Flags
#ADD_DEFINITIONS(-Wall -Wextra)

SET(euclidean-distance-transform_HEADERS
)

SET(euclidean-distance-transform_SOURCES
  main.cpp)

#MESSAGE(STATUS "GLEW_PATH: $ENV{GLEW_PATH}")
#MESSAGE(STATUS "GLFW_PATH: $ENV{GLFW_PATH}")
#MESSAGE(STATUS "NDJINN_PATH: $ENV{NDJINN_PATH}")
#MESSAGE(STATUS "THX_PATH: $ENV{THX_PATH}")

ADD_SUBDIRECTORY(C:/tfs_github/glfw/ lib)

INCLUDE_DIRECTORIES(
  C:/tfs_github/glew-2.0.0-win32/glew-2.0.0/include
  C:/tfs_github/glfw/include
  C:/tfs_github/nDjinn/include
  C:/tfs_github/thx/include)
  #../ppm-io/include)

LINK_DIRECTORIES(
  C:/tfs_github/glew-2.0.0-win32/glew-2.0.0/lib/Release/Win32)

ADD_DEFINITIONS(-DGLEW_STATIC -DNO_TIMER)

ADD_EXECUTABLE(euclidean-distance-transform
  ${euclidean-distance-transform_SOURCES}
  ${euclidean-distance-transform_HEADERS})

TARGET_LINK_LIBRARIES(euclidean-distance-transform
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  glfw
  glew32s)
