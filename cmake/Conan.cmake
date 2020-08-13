macro(run_conan)
    # Download automatically, you can also just copy the conan.cmake file
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(
                STATUS
                "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(NAME CLI11 URL
            https://api.bintray.com/conan/cliutils/CLI11)

    conan_add_remote(NAME bincrafters URL
            https://api.bintray.com/conan/bincrafters/public-conan)

            #blaze/3.7
            #docopt.cpp/0.6.2

    conan_cmake_run(
            REQUIRES
            ${CONAN_EXTRA_REQUIRES}
            CLI11/1.9.1@cliutils/stable
            catch2/2.13.0
            fmt/6.2.1
            spdlog/1.6.1
            nlohmann_json/3.8.0
            OPTIONS
            ${CONAN_EXTRA_OPTIONS}
            BASIC_SETUP
            CMAKE_TARGETS # individual targets to link to
            BUILD
            missing)
endmacro()
