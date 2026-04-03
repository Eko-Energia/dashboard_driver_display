cmake_minimum_required(VERSION 3.16)

project(eko_dash2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR "/home/igor/Qt/6.9.3/gcc_64/lib/cmake/Qt6/")

find_package(Qt6 6.9.3 EXACT REQUIRED COMPONENTS Quick WebSockets)

set(CMAKE_AUTOMOC ON)        
set(CMAKE_AUTORCC ON)     
set(CMAKE_AUTOUIC ON)    

qt_add_executable(appeko_dashboard
    resources.qrc
    inc/blinker.h
    src/blinker.cpp
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
)

include(GNUInstallDirs)
install(TARGETS appeko_dashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
