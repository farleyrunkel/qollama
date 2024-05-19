cmake_minimum_required(VERSION 3.5)

project(qollama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "forms")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}Network REQUIRED)

include_directories("src")

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        forms/mainwindow.ui
)

if(WIN32)
    list(APPEND PROJECT_SOURCES qollama.rc)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qollama
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resouces.qrc
        forms/imessagebox.ui

        src/ihistorylist.h
        src/ioverlaybutton.h
        src/imessagebox.h
        src/imessagebox.cpp

        src/ichatlist.h
        src/ichatitemdelegate.h
        src/ichatitemdelegate.cpp
        src/ichatitemmodel.h
        src/ichatitemmodel.cpp

        src/chatbot.h
        src/chatbot.cpp
        src/ichatlist.cpp
        src/ihistorylist.cpp
        forms/welcomepage.ui
        src/iwelcomepage.h
        src/iwelcomepage.cpp
        src/iwelcomebutton.h
        src/iwelcomebutton.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qollama APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qollama SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qollama
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qollama PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
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
