file(GLOB files
        "*.cpp"
        "*.hpp"
        )

add_library(logic STATIC ${files})

target_link_libraries(logic PRIVATE project_options project_warnings CONAN_PKG::fmt CONAN_PKG::spdlog)
