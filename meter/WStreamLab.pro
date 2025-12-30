# ============================================
# WStreamLab Project Configuration
# ============================================

# Version configuration
# Major.Minor.Build.Revision
VERSION = 1.7.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# ============================================
# BUILD VALIDATION AND TESTS
# ============================================

# Display build configuration
message("===========================================")
message("Building: WStreamLab version $$VERSION")
message("Qt version: $$QT_VERSION")
message("Build directory: $$OUT_PWD")
message("Source directory: $$PWD")
CONFIG(debug, debug|release) {
    message("Build type: DEBUG")
} else {
    message("Build type: RELEASE")
}
message("===========================================")

# Verify critical files exist
!exists(main.cpp) {
    error("main.cpp not found! Cannot build application.")
}

!exists(mainwindow.h) {
    error("mainwindow.h not found! Cannot build application.")
}

!exists(mainwindow.cpp) {
    error("mainwindow.cpp not found! Cannot build application.")
}

# Check UI files
REQUIRED_UI_FILES = \
    mainwindow.ui \
    helpabout.ui \
    license.ui \
    report.ui \
    tableBoard.ui \
    interface.ui

for(file, REQUIRED_UI_FILES) {
    !exists($$file) {
        error("Required UI file missing: $$file")
    }
}

message("All required UI files found: $$size(REQUIRED_UI_FILES) files")

# Windows-specific icon check
win32 {
    !isEmpty(RC_ICONS) {
        !exists($$RC_ICONS) {
            warning("Application icon not found: $$RC_ICONS")
        } else {
            message("Application icon found: $$RC_ICONS")
        }
    }
}

# ============================================
# Qt MODULES
# ============================================

QT += core gui printsupport widgets serialbus

# Verify required modules
!qtHaveModule(serialbus) {
    error("SerialBus module not found! Please install Qt SerialBus.")
}

# ============================================
# COMPILER CONFIGURATION
# ============================================

# Set C++ standard to C++17
CONFIG += c++17

# Enable all warnings and treat them as errors
QMAKE_CXXFLAGS += -Wall -Wextra -Werror

# Compiler identification
*-g++* {
    message("Compiler: GCC/MinGW")
}
*-msvc* {
    message("Compiler: MSVC")
}

# ============================================
# SOURCE FILES
# ============================================

# Source and header files
SOURCES += $$files($$PWD/*.cpp)
HEADERS += $$files($$PWD/*.h)

# Verify we have source files
isEmpty(SOURCES) {
    error("No source files found!")
}

message("Found $$size(SOURCES) source files")
message("Found $$size(HEADERS) header files")

# ============================================
# UI FORMS
# ============================================

FORMS += \
    mainwindow.ui \
    helpabout.ui \
    license.ui \
    report.ui \
    tableBoard.ui \
    interface.ui

# ============================================
# RESOURCES
# ============================================

RESOURCES += resources.qrc

# ============================================
# PLATFORM-SPECIFIC CONFIGURATION
# ============================================

# Include the icon for Windows
win32 {
    RC_ICONS = WStreamLab.ico
}

# ============================================
# TRANSLATIONS
# ============================================

TRANSLATIONS += $$files(translations/*.ts)

# Check if translation files exist
TRANS_FILES = $$files(translations/*.ts)
!isEmpty(TRANS_FILES) {
    message("Found $$size(TRANS_FILES) translation files")
}

# ============================================
# BUILD TARGET
# ============================================

TARGET = WStreamLab

# ============================================
# DEPLOYMENT CONFIGURATION
# ============================================

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# ============================================
# POST-BUILD VALIDATION
# ============================================

win32 {
    QMAKE_POST_LINK += echo "Post-build validation..." &&
    CONFIG(debug, debug|release) {
        QMAKE_POST_LINK += if exist "$$OUT_PWD/debug/$$TARGET.exe" (echo [OK] Debug executable created successfully) else (echo [ERROR] Debug executable not found!)
    } else {
        QMAKE_POST_LINK += if exist "$$OUT_PWD/release/$$TARGET.exe" (echo [OK] Release executable created successfully) else (echo [ERROR] Release executable not found!)
    }
}

unix {
    QMAKE_POST_LINK += echo "[OK] Build completed successfully"
}

# ============================================
# END OF PROJECT FILE
# ============================================
