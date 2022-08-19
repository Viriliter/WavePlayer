cmake_minimum_required(VERSION 3.5)

project(QtMediaPlayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets MultimediaWidgets REQUIRED)
#find_package(${PROJECT_SOURCES}/resources)

#add_library(VLCQt STATIC IMPORTED) # or STATIC instead of SHARED
#set_target_properties(VLCQt PROPERTIES
#  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/vlc/"
#  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/vlc/include/"
#)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ./plugins/qmedianavigator.cpp
        ./plugins/qmedianavigator.h
        ./plugins/qvolumewidget.cpp
        ./plugins/qvolumewidget.h
        ./plugins/qvolumeslider.cpp
        ./plugins/qvolumeslider.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtMediaPlayer
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(QtMediaPlayer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(QtMediaPlayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtMediaPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::MultimediaWidgets ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
