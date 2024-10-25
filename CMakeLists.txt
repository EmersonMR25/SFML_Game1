cmake_minimum_required(VERSION 3.28)
project(SFML_Game LANGUAGES CXX)

# Set output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries (if needed)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML from the repository
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Collect all source files (in the future you can add more here)
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create the executable
add_executable(main ${SOURCES})

# Link SFML libraries
target_link_libraries(main PRIVATE sfml-graphics sfml-system)
target_compile_features(main PRIVATE cxx_std_17)

# Windows-specific settings to copy OpenAL DLL
if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
