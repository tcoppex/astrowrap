# -----------------------------------------------------------------------------
# CMake configuration file (2021 - unlicense.org)
# 
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

project(astrowrap VERSION 1.0 LANGUAGES CXX C)

# -----------------------------------------------------------------------------
# CMake policies.
# -----------------------------------------------------------------------------

# Use <PackageName>_ROOT variables.
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# Do not place MSVC warning flags in the default cache entries.
if(POLICY CMP0092)
  cmake_policy(SET CMP0092 NEW)
endif()

# -----------------------------------------------------------------------------
# Project paths.
# -----------------------------------------------------------------------------

set(ASTROWRAP_ROOT_PATH                   ${CMAKE_CURRENT_SOURCE_DIR})
set(ASTROWRAP_SOURCE_DIR                  ${ASTROWRAP_ROOT_PATH}/src)
set(ASTROWRAP_BINARY_DIR                  ${ASTROWRAP_ROOT_PATH}/bin)

# -----------------------------------------------------------------------------
# CMake general options.
# -----------------------------------------------------------------------------

set(CMAKE_VERBOSE_MAKEFILE          OFF)
set(CMAKE_COLOR_MAKEFILE            ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD   ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
set(CMAKE_DISABLE_SOURCE_CHANGES    OFF)

# Default standards with no extensions.
set(CMAKE_C_STANDARD                11)
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)

# Remove (and disallow) sneaky default flags for targets.
set(CMAKE_CXX_FLAGS                 "" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG           "" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_MINSIZEREL      "" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE         "" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "" CACHE INTERNAL "")

# -----------------------------------------------------------------------------
# Internal configuration attributes.
# -----------------------------------------------------------------------------

# Determines if the build is flagged for full debug mode.
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(DEBUG TRUE)
else()
  set(DEBUG FALSE)
endif()

# Determines the build platform.
if(UNIX AND NOT APPLE AND NOT ANDROID AND NOT WEBGL)
  set(OS_NAME "Linux")
  set(OS_LINUX TRUE)
elseif(WIN32)
  set(OS_NAME "Windows")
  set(OS_WIN32 TRUE)
else()
  message(WARNING "The \"${CMAKE_SYSTEM_NAME}\" platform is not officially supported.")
endif()

# Determines the current compiler.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(USE_GCC TRUE)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
  set(USE_CLANG TRUE)
elseif(MSVC)
  set(USE_MSVC TRUE)
else()
  message(WARNING "The \"${CMAKE_CXX_COMPILER_ID}\" compiler is not officially supported.")
endif()

# -----------------------------------------------------------------------------
# Compiler settings.
# -----------------------------------------------------------------------------

if(USE_GCC OR USE_CLANG)
  # This is a mix of warning options not available in all GCC / Clang version.
  list(APPEND CXX_FLAGS 
    -Wall -Wextra -Wpedantic
    -Wcast-align
    -Wlogical-op
    -Wnull-dereference
    -Wformat=2 -Wformat-truncation -Wformat-overflow
    -Wdisabled-optimization
    -Wno-missing-field-initializers
    -Wno-unused-function 
    -Wno-unused-parameter
    -Wno-write-strings
    -Wno-format-nonliteral
    -Wno-misleading-indentation
    -Wvector-operation-performance
  )

  # To avoid warnings about the previous mismatched GCC / Clang options.
  if (USE_CLANG)
    list(APPEND CXX_FLAGS -Wno-unknown-warning-option)
  endif()

  # Features.
  list(APPEND CXX_FLAGS
    -fdiagnostics-color
    -fvisibility=hidden 
    -fno-strict-aliasing 
    -fno-builtin-memcmp
    -fno-common
    -ffunction-sections
    -fdata-sections
  )

  list(APPEND CXX_FLAGS_DEBUG           -O0 -g3 -Wconversion -Wundef)
  list(APPEND CXX_FLAGS_RELEASE         -O2)
  list(APPEND CXX_FLAGS_RELWITHDEBINFO  ${CXX_FLAGS_RELEASE} -g)
  
  # Linker flags.
  list(APPEND CustomLinkFlags 
    -Wl,--no-undefined 
    -Wl,--gc-sections 
    -Wl,--color-diagnostics
  )
elseif(USE_MSVC)
  list(APPEND CXX_FLAGS
    /W4 
    /w14640   # enable warning on thread un-safe static member initialization.
    /w14928   # illegal copy-initialization.
    /w14265   # class has virtual functions, but destructor is not virtual.
    /w14555   # expression with no effect or side-effect.
    /wd4100   # keep unused parameters
    /MP       # build with multiple process.
    #/EHsc-    # no exception.
    #/GR-      # disable RTTI.
    /permissive-
  )
  list(APPEND CXX_FLAGS_DEBUG           /Zi)
  list(APPEND CXX_FLAGS_RELEASE         /Ox /INCREMENTAL:NO /DEBUG:NONE /DNDEBUG)
  list(APPEND CXX_FLAGS_RELWITHDEBINFO  ${CXX_FLAGS_RELEASE} /Ox /Zi)
 
  list(APPEND CustomDefinitions 
   -DNOMINMAX
   -DWIN32
   -D_WINDOWS
   -D_CRT_SECURE_NO_WARNINGS
   -D_HAS_EXCEPTIONS=0
   -DVC_EXTRALEAN
   -DWIN32_LEAN_AND_MEAN
  )
endif()

list(APPEND CustomDefinitions
  -DNO_SWE_GLP
)

# -----------------------------------------------------------------------------
# Sources.
# -----------------------------------------------------------------------------

file(GLOB_RECURSE Sources
  ${ASTROWRAP_SOURCE_DIR}/*.h
  ${ASTROWRAP_SOURCE_DIR}/*.c
  ${ASTROWRAP_SOURCE_DIR}/*.cc
)


list(APPEND CustomIncludeDirs
  ${ASTROWRAP_SOURCE_DIR}
) 

# -----------------------------------------------------------------------------
# Target properties and build parameters.
# -----------------------------------------------------------------------------

set(TARGET_NAME ${CMAKE_PROJECT_NAME})

add_executable(${TARGET_NAME} ${Sources})

# Set targets properties.
list(APPEND Targets ${TARGET_NAME})

foreach(target ${Targets})
  target_compile_options(
    ${target}
    PRIVATE
      "${CXX_FLAGS}"
      "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
      "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>"
      "$<$<CONFIG:DebugWithRelInfo>:${CXX_FLAGS_RELWITHDEBINFO}>"
  )
  target_compile_definitions(${target} PRIVATE ${CustomDefinitions})
  target_include_directories(${target} PRIVATE ${CustomIncludeDirs})
  target_link_libraries(${target} PRIVATE ${CustomLibs})
  set_target_properties(${target} PROPERTIES LINK_FLAGS ${CustomLinkFlags})

  # Force Debug / Release output in the same directory (for MSVC).
  foreach(type RUNTIME LIBRARY ARCHIVE)
    set_target_properties(${target} PROPERTIES
      ${type}_OUTPUT_DIRECTORY         ${ASTROWRAP_BINARY_DIR}
      ${type}_OUTPUT_DIRECTORY_DEBUG   ${ASTROWRAP_BINARY_DIR}
      ${type}_OUTPUT_DIRECTORY_RELEASE ${ASTROWRAP_BINARY_DIR}
    )
  endforeach()
endforeach()

# -----------------------------------------------------------------------------
