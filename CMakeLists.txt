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
# Qt5 - Provide path via -DCMAKE_PREFIX_PATH if needed
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

# --- Version (pass -DAPP_VERSION=x.y.z from CI, defaults to 0.0.0) ---
if(NOT DEFINED APP_VERSION)
    set(APP_VERSION "0.0.0")
endif()

# --- Platform-Specific Database Linking ---
if(UNIX AND NOT APPLE)
    # Linux/MariaDB (e.g. on Debian-based systems)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MYSQL REQUIRED IMPORTED_TARGET libmariadb)

elseif(WIN32)
    # Manual MySQL path setup for Windows
    set(MySQL_INCLUDE_DIR "C:/Program Files/MySQL/MySQL Server 8.0/include")
    set(MySQL_LIBRARY "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")
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
        updatechecker.cpp
        updatechecker.h
        resources.qrc
        constants.h
)

target_compile_definitions(InventorySystem PRIVATE APP_VERSION="${APP_VERSION}")

# --- Linking Libraries ---
target_link_libraries(InventorySystem PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)

if(UNIX AND NOT APPLE)
    target_link_libraries(InventorySystem PRIVATE PkgConfig::MYSQL)
elseif(WIN32)
    target_include_directories(InventorySystem PRIVATE ${MySQL_INCLUDE_DIR})
    target_link_libraries(InventorySystem PRIVATE ${MySQL_LIBRARY})
endif()

# --- Platform-Specific Post-Build Steps ---
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "Minimum macOS deployment version" FORCE)
endif()

if(WIN32)
    set_target_properties(InventorySystem PROPERTIES WIN32_EXECUTABLE YES)

    # Copy MySQL DLL
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    # Copy Qt DLLs and plugin
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
