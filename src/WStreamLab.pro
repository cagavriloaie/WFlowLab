# ============================================
# WStreamLab Project Configuration
# ============================================

# Version configuration
# Major.Minor.Build.Revision
VERSION = 1.8.0.0
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

!exists(MainWindow.h) {
    error("MainWindow.h not found! Cannot build application.")
}

!exists(MainWindow.cpp) {
    error("MainWindow.cpp not found! Cannot build application.")
}

# Check UI files
REQUIRED_UI_FILES = \
    MainWindow.ui \
    HelpAbout.ui \
    License.ui \
    Report.ui \
    TableBoard.ui \
    Interface.ui

for(file, REQUIRED_UI_FILES) {
    !exists($$file) {
        error("Required UI file missing: $$file")
    }
}

message("All required UI files found: $$size(REQUIRED_UI_FILES) files")

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

# Enable warnings
CONFIG += warn_on

# Compiler-specific warning and error settings
*-g++* {
    message("Compiler: GCC/MinGW")
    # Enable all warnings, extra warnings, and treat them as errors
    QMAKE_CXXFLAGS += -Wall -Wextra -Werror -pedantic
    # Show all errors during compilation
    QMAKE_CXXFLAGS += -fmax-errors=0
}

*-msvc* {
    message("Compiler: MSVC")
    # Enable maximum warning level and treat warnings as errors
    QMAKE_CXXFLAGS += /W4 /WX
    # Disable specific warnings that are too strict for Qt
    QMAKE_CXXFLAGS += /wd4127  # conditional expression is constant (Qt macros)
    QMAKE_CXXFLAGS += /wd4512  # assignment operator could not be generated
}

# ============================================
# GENERATED FILES DIRECTORIES
# ============================================

# Keep generated files separate from source code
# This prevents ui_*.h, moc_*.cpp, and other build artifacts
# from cluttering the source directory
UI_DIR = $$OUT_PWD/generated/ui
MOC_DIR = $$OUT_PWD/generated/moc
RCC_DIR = $$OUT_PWD/generated/rcc
OBJECTS_DIR = $$OUT_PWD/obj

message("Generated files directory: $$OUT_PWD/generated")

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
    MainWindow.ui \
    HelpAbout.ui \
    License.ui \
    Report.ui \
    TableBoard.ui \
    Interface.ui

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

    # Icon check must stay after RC_ICONS is assigned, otherwise it never runs
    !isEmpty(RC_ICONS) {
        !exists($$RC_ICONS) {
            warning("Application icon not found: $$RC_ICONS")
        } else {
            message("Application icon found: $$RC_ICONS")
        }
    }
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

# The post-link command is emitted verbatim into the Makefile and executed by
# sh.exe, not cmd.exe. Nested double quotes and a backslash before a closing
# quote break the shell, so keep this free of quotes and of "cmd /c" wrappers.
win32 {
    CONFIG(debug, debug|release) {
        DEPLOY_DIR = $$shell_path($$OUT_PWD/debug)
    } else {
        DEPLOY_DIR = $$shell_path($$OUT_PWD/release)
    }
    DOC_DIR = $$shell_path($$PWD/..)

    QMAKE_POST_LINK += copy /Y $$DOC_DIR\\PROCES_CALCUL_VERIFICARE_CONTOARE.md $$DEPLOY_DIR > nul &
    QMAKE_POST_LINK += copy /Y $$DOC_DIR\\VERIFICATION_METHOD_PROCESS.md $$DEPLOY_DIR > nul
}

unix {
    QMAKE_POST_LINK += echo "[OK] Build completed successfully"
}

# ============================================
# END OF PROJECT FILE
# ============================================
