cmake_minimum_required(VERSION 3.5)
project(Engenie VERSION 1.0.0 LANGUAGES C CXX)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

if(NOT MSVC)
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
        set(SFML_DIR "~/sfml")
    endif()
endif()

file(GLOB PROJECT_SOURCES src/*.cpp)

add_subdirectory(vendor/glm)
add_subdirectory(vendor/json)
add_subdirectory(vendor/sfml)
add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
find_package(SFML 2.5 COMPONENTS graphics audio system window network REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} vendor/glad/src/glad.c)
include_directories(include vendor/glad/include)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(Engenie ${GLAD_LIBRARIES} nlohmann_json::nlohmann_json glm sfml-system sfml-window sfml-graphics sfml-network sfml-audio)