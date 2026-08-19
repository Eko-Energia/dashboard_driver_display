cmake_minimum_required(VERSION 3.16)

option(CROSS_COMPILE "Cross-kompilacja na ARM" OFF)

if(CROSS_COMPILE)
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR aarch64)
    set(CMAKE_C_COMPILER "/usr/bin/aarch64-linux-gnu-gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-linux-gnu-g++")
    
    # QT skompilowane na arm'a
    set(QT_PATH "$ENV{HOME}/Documents/projects_cpp/cross-comp/qt-raspi")
    # Sysroot malinki (tez potrzzebny)
    set(CMAKE_SYSROOT "$ENV{HOME}/Documents/projects_cpp/cross-comp/rpi-sysroot")

    # pkg-config czasem myli gdzie ma szukac bibliotek
    set(ENV{PKG_CONFIG_SYSROOT_DIR} "${CMAKE_SYSROOT}")
    set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig")
    set(ENV{PKG_CONFIG_PATH} "") 

    set(CMAKE_FIND_ROOT_PATH "${QT_PATH}" "${CMAKE_SYSROOT}")

    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER) 
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY) 
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)  
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY) 
else()
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
    set(QT_PATH "$ENV{HOME}/Qt/6.9.3/gcc_64")         
endif()

project(eko_dash2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "${QT_PATH}")
find_package(Qt6 6.9.3 EXACT REQUIRED COMPONENTS Quick WebSockets Core5Compat)

set(CMAKE_AUTOMOC ON)        
set(CMAKE_AUTORCC ON)     
set(CMAKE_AUTOUIC ON)    

qt_add_executable(appeko_dashboard
    resources.qrc
    inc/clock.h
    src/clock.cpp
    src/main.cpp
    inc/websocketclient.h 
    src/websocketclient.cpp
    inc/functions.h 
    src/functions.cpp
    inc/system.h
    src/system.cpp
)


target_include_directories(appeko_dashboard
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appeko_dashboard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appeko_dashboard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appeko_dashboard
    PRIVATE Qt6::Quick
    PRIVATE Qt6::WebSockets
    PRIVATE Qt6::Core5Compat
)

include(GNUInstallDirs)
install(TARGETS appeko_dashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
