cmake_minimum_required(VERSION 3.5)

project(gnusician LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets UiTools REQUIRED)

include_directories(qt-material-widgets/components)
add_subdirectory(qt-material-widgets/components)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        loginmanager.cpp
        loginmanager.h
        navigationdrawer.cpp
        navigationdrawer.h
        common.cpp
        common.h
        userinfo.cpp
        userinfo.h
        mainwindow.ui
        loginmanager.ui
        navigationdrawer.ui
)

add_executable(gnusician
    ${PROJECT_SOURCES}
    resources/appresources.qrc
)

target_link_libraries(gnusician PRIVATE Qt5::Core Qt5::Widgets Qt5::UiTools material)
target_include_directories(gnusician PUBLIC ./ ./qt-material-widgets/components)
install(TARGETS gnusician DESTINATION bin)
install(TARGETS material DESTINATION lib)


