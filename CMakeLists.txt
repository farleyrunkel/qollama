cmake_minimum_required(VERSION 3.5)

project(qollama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

if (Python3_FOUND)
    message(STATUS "Python3 found")
    message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
    message(STATUS "Python3_LIBRARIES: ${Python3_LIBRARIES}")
    message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
    include_directories(${Python3_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Python3 not found")
endif()

# Include the src directory and all its subdirectories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Find all direct subdirectories under the src directory
file(GLOB SUBDIRS RELATIVE ${SRC_DIR} ${SRC_DIR}/*)
foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${SRC_DIR}/${subdir})
        include_directories(${SRC_DIR}/${subdir})
    endif()
endforeach()

include_directories("external/json/include")
include_directories("external/asio/asio/include")
include_directories("external/ollama/include")

# Set the main file
if(APPLE)
    # Set the application icon on macOS
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set(app_icon_macos ${CMAKE_SOURCE_DIR}/resources/icon.icns)
    # Output icon path for debugging
    message(STATUS "Icon file path: ${app_icon_macos}")

    # Ensure the icon file path is correct
    if(NOT EXISTS ${app_icon_macos})
        message(FATAL_ERROR "Icon file not found: ${app_icon_macos}")
    else()
        message(STATUS "Icon file found: ${app_icon_macos}")
    endif()

    set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    # Set the Info.plist file
    set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/Info.plist)

    set(PROJECT_MAIN_FILE "src/main.mm")
else()
    set(PROJECT_MAIN_FILE "src/main.cpp")
endif()

# Find all source and header files in all subdirectories under the src directory
file(GLOB_RECURSE PROJECT_SOURCES
    "${SRC_DIR}/*/*.cpp"
    "${SRC_DIR}/*/*.h"
)

# Add the main file to PROJECT_SOURCES
list(APPEND PROJECT_SOURCES ${PROJECT_MAIN_FILE})

if(APPLE)
    list(APPEND PROJECT_SOURCES ${app_icon_macos})
endif()

# Create the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qollama
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resources.qrc
    )
else()
    if(ANDROID)
        add_library(qollama SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qollama
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link ws2_32 library only on Windows
if(WIN32)
    target_link_libraries(qollama PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ${Python3_LIBRARIES} ws2_32)
else()
    target_link_libraries(qollama PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ${Python3_LIBRARIES})
endif()

# Set some properties on macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.qollama)
endif()

set_target_properties(qollama PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(APPLE)
    install(FILES ${app_icon_macos} DESTINATION ${CMAKE_INSTALL_PREFIX}/Contents/Resources)
    install(FILES ${MACOSX_BUNDLE_INFO_PLIST} DESTINATION ${CMAKE_INSTALL_PREFIX}/Contents)
endif()

include(GNUInstallDirs)
install(TARGETS qollama
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qollama)
endif()

add_subdirectory(tests)
