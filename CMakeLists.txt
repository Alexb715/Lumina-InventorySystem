cmake_minimum_required(VERSION 3.27)
project(InventorySystem)

# --- Common Settings for All Platforms ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# --- Platform-Specific Compiler Flags ---
if(UNIX)
    # Compiler flags for Linux and macOS
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -flto -march=native")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -flto -march=native")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_DEBUG "-g")
endif()

# --- Find Dependencies ---
# Qt5 - Finds Qt libraries for all platforms.
# For Windows/macOS, you may need to tell CMake where to find Qt by setting
# CMAKE_PREFIX_PATH, e.g., -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/mingw81_64"
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# MySQL/MariaDB - Find the database client library for each OS
if(UNIX AND NOT APPLE)
    # For Linux, use pkg-config to find MariaDB client
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MYSQL REQUIRED IMPORTED_TARGET libmariadb)

elseif(WIN32 OR APPLE)
    # For Windows and macOS, use CMake's FindMySQL module.
    # On Windows, you may need to set -DMySQL_DIR="C:/Program Files/MySQL/MySQL Server 8.0"
    # On macOS, Homebrew should configure this to work automatically.
    find_package(MySQL REQUIRED)
endif()


# --- Executable Definition ---
add_executable(InventorySystem
        main.cpp
        DatabaseController.cpp
        DatabaseController.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        loginwindow.cpp
        loginwindow.h
        loginwindow.ui
)

# --- Linking Libraries ---
# Link Qt libraries (common to all)
target_link_libraries(InventorySystem PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Link platform-specific database library
if(UNIX AND NOT APPLE)
    target_link_libraries(InventorySystem PRIVATE PkgConfig::MYSQL)
elseif(WIN32 OR APPLE)
    target_include_directories(InventorySystem PRIVATE ${MySQL_INCLUDE_DIR})
    target_link_libraries(InventorySystem PRIVATE MySQL::Client)
endif()

# --- Platform-Specific Post-Build Steps ---

if(APPLE)
    # Set minimum required macOS version
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "Minimum macOS deployment version" FORCE)
endif()

if(WIN32)
    # Use WIN32_EXECUTABLE to hide the console window on launch
    set_target_properties(InventorySystem PROPERTIES WIN32_EXECUTABLE YES)

    # Custom command to copy required Qt and MySQL DLLs to the build directory
    # so the application can be run directly from the build folder.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MySQL_LIBRARY}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    # This script locates the Qt installation and copies the necessary platform plugin
    # and core DLLs next to your compiled executable.
    set(DEBUG_SUFFIX "")
    if(MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()

    get_target_property(QT_DLL_LOCATION Qt5::Core LOCATION)
    get_filename_component(QT_BIN_DIR ${QT_DLL_LOCATION} DIRECTORY)
    get_filename_component(QT_INSTALL_PATH ${QT_BIN_DIR} DIRECTORY)

    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()

    foreach(QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach()
endif()