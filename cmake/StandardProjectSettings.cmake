# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui, ccmake
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based
# tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" ON)

if(ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        message("IPO enabled: ${output}")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message("IPO is not supported: ${output}")
    endif()
endif()

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)

option(ENFORCE_NATIVE_ARC "Force march=native for compiler" ON)
if (ENFORCE_NATIVE_ARC)
    add_definitions("-march=native")
else()
    add_definitions("-mavx2")
endif()

add_definitions("-funroll-loops")
if (WIN32)
    add_definitions("-fno-rtti")
endif()

option(ENABLE_FPERMISSIVE "Set -fpermissive" OFF)
if (ENABLE_FPERMISSIVE)
    add_definitions("-fpermissive")
endif()

option(ENABLE_STRIPPING "Enables binary stripping (reduce file size) (aka -s)" ON)
if (ENABLE_STRIPPING)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
endif()
