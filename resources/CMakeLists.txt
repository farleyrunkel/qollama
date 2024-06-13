cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(resources)

# Set configuration variables
set(MODELDIR ${CMAKE_SOURCE_DIR}/models)

if (EXISTS ${CMAKE_INSTALL_PREFIX}/models)
    set(MODELDIR ${CMAKE_INSTALL_PREFIX}/models)
endif()

set(GPTSDIR ${CMAKE_SOURCE_DIR}/external/gpts)

if (EXISTS ${CMAKE_INSTALL_PREFIX}/gpts)
    set(GPTSDIR ${CMAKE_INSTALL_PREFIX}/gpts)
endif()

# Debug messages
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "GPTSDIR: ${GPTSDIR}")

# Generate the config.json file
configure_file(${CMAKE_SOURCE_DIR}/resources/config.json.in ${CMAKE_BINARY_DIR}/config.json @ONLY)

if(APPLE)
    # On macOS, install models folder and config file into the app bundle
    install(FILES ${CMAKE_BINARY_DIR}/config.json DESTINATION ${CMAKE_INSTALL_PREFIX}/qollama.app/Contents/Resources)
else()
    # On other systems, install models folder and config file into the install prefix
    install(FILES ${CMAKE_BINARY_DIR}/config.json DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
