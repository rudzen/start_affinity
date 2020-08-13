
add_executable(start_affinity main.cpp)

target_link_libraries(start_affinity PRIVATE logic cli project_options project_warnings CONAN_PKG::fmt CONAN_PKG::spdlog)
