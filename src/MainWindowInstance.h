/**
 * \file MainWindowInstance.h
 * \brief Thread-safe singleton access to MainWindow instance
 *
 * This file provides a thread-safe way to access the MainWindow instance
 * from any part of the application, eliminating the need for global pointers.
 *
 * \author Constantin
 * \date 2025-12-31
 */

#ifndef MAINWINDOWINSTANCE_H
#define MAINWINDOWINSTANCE_H

#include <mutex>

// Forward declaration
class MainWindow;

/**
 * \brief Thread-safe singleton for MainWindow access
 *
 * This class provides static methods to set and get the MainWindow instance
 * in a thread-safe manner, eliminating dangerous global pointers.
 */
class MainWindowInstance {
public:
    /**
     * \brief Set the MainWindow instance (called from MainWindow constructor)
     * \param window Pointer to the MainWindow instance
     */
    static void setInstance(MainWindow* window);

    /**
     * \brief Get the MainWindow instance
     * \return Pointer to MainWindow, or nullptr if not set
     */
    static MainWindow* getInstance();

    /**
     * \brief Clear the MainWindow instance (called from MainWindow destructor)
     */
    static void clearInstance();

private:
    static MainWindow* instance;
    static std::mutex mutex;

    // Prevent instantiation
    MainWindowInstance() = delete;
    ~MainWindowInstance() = delete;
    MainWindowInstance(const MainWindowInstance&) = delete;
    MainWindowInstance& operator=(const MainWindowInstance&) = delete;
};

#endif // MAINWINDOWINSTANCE_H
