cmake_minimum_required(VERSION 3.5)

project(qollama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# 包含 src 目录及其所有子目录
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# 查找 src 目录下的所有直接子目录
file(GLOB SUBDIRS RELATIVE ${SRC_DIR} ${SRC_DIR}/*)
foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${SRC_DIR}/${subdir})
        include_directories(${SRC_DIR}/${subdir})
    endif()
endforeach()

include_directories("external/json/include")
include_directories("external/asio/asio/include")
include_directories("external/ollama/include")

# 设置主文件
if(WIN32)
    set(PROJECT_MAIN_FILE "src/main.cpp")
else()
    set(PROJECT_MAIN_FILE "src/main.mm")
endif()


# 查找 src 目录下所有子目录中的所有源文件和头文件
file(GLOB_RECURSE PROJECT_SOURCES
    "${SRC_DIR}/*/*.cpp"
    "${SRC_DIR}/*/*.h"
)

# 将主文件添加到 PROJECT_SOURCES
list(APPEND PROJECT_SOURCES ${PROJECT_MAIN_FILE})

# 创建可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qollama
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resouces.qrc

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

# 只在 Windows 上链接 ws2_32 库
if(WIN32)
    target_link_libraries(qollama PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ws2_32)
else()
    target_link_libraries(qollama PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
endif()

# 设置 macOS 下的一些属性
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
