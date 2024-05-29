cmake_minimum_required(VERSION 3.5)

project(qollama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "forms")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}Network REQUIRED)

include_directories("src")

include_directories("src/buttons")
include_directories("src/network")
include_directories("src/display")
include_directories("src/input")
include_directories("src/pages")
include_directories("src/tests")
include_directories("src/container")
include_directories("src/objects")
include_directories("src/3rdParty/spinner")

include_directories("external/json/include")
include_directories("external/asio/asio/include")
include_directories("external/ollama/include")

set(PROJECT_SOURCES
        src/main.cpp
        forms/mainwindow.ui
        forms/welcomepage.ui

        src/network/client.h src/network/client.cpp

        src/buttons/ioverlaybutton.h
        src/buttons/imacbuttonswidget.h src/buttons/imacbuttonswidget.cpp
        src/buttons/iwinbuttonswidget.h src/buttons/iwinbuttonswidget.cpp

        src/display/ipushcard.h src/display/ipushcard.cpp

        src/container/ihistorylist.h  src/container/ihistorylist.cpp
        src/container/igallerywidget.h src/container/igallerywidget.cpp
        src/container/ichatwidget.h  src/container/ichatwidget.cpp

        src/pages/iwelcomepage.h src/pages/iwelcomepage.cpp
        src/pages/mainwindow.h src/pages/mainwindow.cpp
        src/pages/imarketpage.h src/pages/imarketpage.cpp

        src/tests/itestwidget.h src/tests/itestwidget.cpp
)

if(WIN32)
    list(APPEND PROJECT_SOURCES resources/qollama.rc)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qollama
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resouces.qrc

        src/3rdParty/spinner/waitingspinnerwidget.h
        src/3rdParty/spinner/waitingspinnerwidget.cpp
        src/container/iwidget.h src/container/iwidget.cpp
        src/display/iautoresizetextbrowser.h src/display/iautoresizetextbrowser.cpp
        src/objects/imageloader.h src/objects/imageloader.cpp
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
