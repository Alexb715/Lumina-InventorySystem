cmake_minimum_required(VERSION 3.27)
project(InventorySystem)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "Minimum macOS deployment version" FORCE)

# Qt5 paths
set(CMAKE_PREFIX_PATH "/Users/alexandrebeaulieu/Qt/5.15.2/clang_64/lib/cmake")

# MySQL paths
set(MYSQL_INCLUDE_DIR "/usr/local/opt/mysql/include")
set(MYSQL_LIBRARY "/usr/local/opt/mysql/lib/libmysqlclient.dylib")

include_directories(${MYSQL_INCLUDE_DIR})
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

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

target_link_libraries(InventorySystem
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${MYSQL_LIBRARY}
)
