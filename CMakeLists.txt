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
    include_directories(${Python3_INCLUDE_DIRS})
else()
    message(STATUS "Python3 not found")
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

# Find all source and header files in all subdirectories under the src directory
file(GLOB PROJECT_SOURCES
    "${SRC_DIR}/*/*.cpp"
    "${SRC_DIR}/*/*.h"
)

add_subdirectory(src/3rdParty/qgallerywidget)
include_directories(${QGALLERYWIDGET_INCLUDE})
list(APPEND PROJECT_SOURCES ${QGALLERYWIDGET_SOURCES})

# Set the main file
if(APPLE)
    # Set the application icon on macOS
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set(APP_ICON_PATH ${CMAKE_SOURCE_DIR}/resources/icon.icns)
    # Output icon path for debugging
    message(STATUS "Icon file path: ${APP_ICON_PATH}")

    # Ensure the icon file path is correct
    if(NOT EXISTS ${APP_ICON_PATH})
        message(FATAL_ERROR "Icon file not found: ${APP_ICON_PATH}")
    else()
        message(STATUS "Icon file found: ${APP_ICON_PATH}")
    endif()

    set_source_files_properties(${APP_ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    # Set the Info.plist file
    set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/Info.plist)
    list(APPEND PROJECT_SOURCES ${APP_ICON_PATH})

    set(PROJECT_MAIN_FILE "src/main.mm")

else()
    list(APPEND PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/resources/resources.rc)
    set(PROJECT_MAIN_FILE "src/main.cpp")
endif()

# Add the main file to PROJECT_SOURCES
list(APPEND PROJECT_SOURCES ${PROJECT_MAIN_FILE})

# Create the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qollama
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resources.qrc

        src/3rdParty/spinner/waitingspinnerwidget.cpp
        src/3rdParty/spinner/waitingspinnerwidget.h
        src/objects/dataloader.h src/objects/dataloader.cpp
        src/display/igptswidget.h src/display/igptswidget.cpp
        src/pages/imodelspage.h src/pages/imodelspage.cpp
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

# if(APPLE)
#     install(FILES ${APP_ICON_PATH} DESTINATION ${CMAKE_INSTALL_PREFIX}/qollama.app/Contents/Resources)
#     install(FILES ${MACOSX_BUNDLE_INFO_PLIST} DESTINATION ${CMAKE_INSTALL_PREFIX}/qollama.app/Contents)
# endif()

include(GNUInstallDirs)
install(TARGETS qollama
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qollama)
endif()

if(APPLE)
    # On macOS, install models folder and config file into the app bundle
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/models DESTINATION ${CMAKE_INSTALL_PREFIX}/qollama.app/Contents)
else()
    # On other systems, install models folder and config file into the install prefix
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/models DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/gpts DESTINATION ${CMAKE_INSTALL_PREFIX})

endif()

add_subdirectory(tests)
add_subdirectory(resources)
