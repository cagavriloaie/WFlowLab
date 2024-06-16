cmake_minimum_required(VERSION 3.5)
project(WStreamLab)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt packages
find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport SerialBus REQUIRED)

# Optional: Include specific modules for Qt versions greater than 4
if(Qt5_VERSION VERSION_GREATER "4")
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    interface.cpp
    helpabout.cpp
    ledindicator.cpp
    license.cpp
    md5.cpp
    report.cpp
    tableBoard.cpp
    waterdensity.cpp
)

# Header files
set(HEADERS
    mainwindow.h
    interface.h
    definitions.h
    flow-meter-type.h
    helpabout.h
    ledindicator.h
    license.h
    md5.h
    report.h
    tableBoard.h
    waterdensity.h
)

# UI form files
set(FORMS
    mainwindow.ui
    interface.ui
    helpabout.ui
    license.ui
    report.ui
    tableBoard.ui
)

# Set translations
set(TRANSLATIONS
    translations/meter_ro_RO.ts
    translations/meter_en_EN.ts
)

# Generate translation files
qt5_add_translation(QM_FILES ${TRANSLATIONS})

# Resource files
set(RESOURCES
    images.qrc
)

# Compile resources
qt5_add_resources(RESOURCE_FILES ${RESOURCES})

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCE_FILES} ${QM_FILES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::SerialBus
)

# Deployment configuration (example paths, adjust as needed)
if(WIN32)
    set(DEPLOY_PATH "${CMAKE_INSTALL_PREFIX}/bin")
else()
    set(DEPLOY_PATH "/opt/${PROJECT_NAME}/bin")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${DEPLOY_PATH})

# Specify additional installation files
install(FILES water-meter-counter-equipment.png DESTINATION ${DEPLOY_PATH})
