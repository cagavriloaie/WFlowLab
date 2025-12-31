/**
 * \file MainWindowInstance.cpp
 * \brief Implementation of thread-safe MainWindow singleton
 *
 * \author Constantin
 * \date 2025-12-31
 */

#include "MainWindowInstance.h"
#include <QDebug>

// Initialize static members
MainWindow* MainWindowInstance::instance = nullptr;
std::mutex MainWindowInstance::mutex;

void MainWindowInstance::setInstance(MainWindow* window) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance != nullptr && window != nullptr) {
        qWarning() << "MainWindowInstance::setInstance() called but instance already exists!";
    }
    instance = window;
}

MainWindow* MainWindowInstance::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        qWarning() << "MainWindowInstance::getInstance() called but instance is null!";
    }
    return instance;
}

void MainWindowInstance::clearInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    instance = nullptr;
}
