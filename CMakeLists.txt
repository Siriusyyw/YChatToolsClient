cmake_minimum_required(VERSION 3.5)

project(YChatTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_FRAMELESSHEPLER OFF)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

if(ANDROID)
    add_library(YChatTools SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(YChatTools
      main.cpp
      chatmanage.cpp chatmanage.h
      clientsocket.h clientsocket.cpp
      chatmessage.h chatmessage.cpp
      chatmodel.h chatmodel.cpp
      packet.h packet.cpp
      qml.qrc
    )
endif()

target_compile_definitions(YChatTools
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(YChatTools
  PRIVATE Qt5::Core Qt5::Quick Qt5::Network
  fluentuiplugin
)

add_subdirectory(FluentUI)
