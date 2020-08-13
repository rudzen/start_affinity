file(GLOB files
        "*.cpp"
        "*.hpp"
        )

# include(FetchContent)
# FetchContent_Declare(
#   cli11
#   GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
# )

# FetchContent_GetProperties(cli11)
# if(NOT cli11_POPULATED)
#   FetchContent_Populate(cli11)
#   add_subdirectory(${cli11_SOURCE_DIR} ${cli11_BINARY_DIR})
# endif()

add_library(cli STATIC ${files})

target_link_libraries(cli PRIVATE project_options project_warnings CONAN_PKG::CLI11)

#target_link_libraries(cli PRIVATE project_options project_warnings  CLI11)
