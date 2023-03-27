cmake_minimum_required(VERSION 3.5)

project(contor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport Core)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        dialog.h
        dialog.cpp
        dialog.ui
        flow-meter-type.h
        air-density.h
        air-density.cpp
        md5.h
        md5.cpp
        licence.h
        licence.cpp
        licence.ui
        helpabout.h
        helpabout.cpp
        helpabout.ui
        resourcescontor.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(contor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET contor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(contor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(contor
            ${PROJECT_SOURCES}
            ${APP_ICON_RESOURCE_WINDOWS}
        )
    endif()
endif()


target_link_libraries(contor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(contor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(TRANSLATE_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        dialog.h
        dialog.cpp
        dialog.ui
        flow-meter-type.h
        air-density.h
        air-density.cpp
        md5.h
        md5.cpp
        licence.h
        licence.cpp
        licence.ui
        helpabout.h
        helpabout.cpp
        helpabout.ui
)

file(GLOB TS_FILES
    ${CMAKE_SOURCE_DIR}romanian.ts
    ${CMAKE_SOURCE_DIR}/english.ts)

qt_add_lupdate(contor TS_FILES romanian.ts english.ts
                      SOURCES ${TRANSLATE_SOURCES})


install(TARGETS contor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(contor)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "WStreamLab")

