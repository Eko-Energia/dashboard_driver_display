cmake_minimum_required(VERSION 3.16)

project(eko_dash2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Chlopie ustaw dobra sciezke do biblioteki!
# LINUX home/User/Qt/wersja_qt/kompilator/lib/cmake
# Windows C:/Qt/wersja_qt/kompilator/lib/cmake
# Jak bedzie finalny frontend deski zrobiony to spakuje te biblioteki tak zeby sie dalo kompilowac bez QT zanstalowanego

set(CMAKE_PREFIX_PATH /home/igor/Qt/6.9.2/gcc_64)
find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

set(CMAKE_AUTORCC ON)
qt_add_executable(appeko_dashboard
    resources.qrc
    inc/dbc.h
    src/dbc.cpp
    inc/can.h
    src/can.cpp
    inc/blinker.h
    src/blinker.cpp
    inc/clock.h
    src/clock.cpp
    inc/valueinfo.h
    src/valueinfo.cpp
    inc/system.h
    src/system.cpp
    src/main.cpp
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
)

include(GNUInstallDirs)
install(TARGETS appeko_dashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
