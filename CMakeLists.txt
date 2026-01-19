cmake_minimum_required(VERSION 3.16)

project(plasma-simplemenu)

set(QT_DEFAULT_MAJOR_VERSION 6)
set(QT_NO_CREATE_VERSIONLESS_TARGETS TRUE)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(KDE_INSTALL_QMLDIR "lib/qt6/qml" CACHE STRING "" FORCE)

find_package(Qt6 REQUIRED COMPONENTS REQUIRED NO_DEFAULT_PATH COMPONENTS
    Core
    Quick
    Widgets
    PATHS /usr/lib/cmake/Qt6
)

find_package(KF6 REQUIRED COMPONENTS
    Service
    I18n
)

find_package(Plasma REQUIRED)
find_package(PlasmaQuick REQUIRED)

add_library(simplemenu MODULE
    plugin/simplemenu.cpp
    plugin/simplemenu.h
    plugin/plugin.cpp
    plugin/qmldir
)

set_target_properties(simplemenu PROPERTIES
    OUTPUT_NAME simplemenu
    POSITION_INDEPENDENT_CODE ON
    SOVERSION 1
)

target_link_libraries(simplemenu
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
    KF6::Service
    KF6::I18n
    Plasma::Plasma
    Plasma::PlasmaQuick
)

message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Full QML path = ${CMAKE_INSTALL_PREFIX}/${KDE_INSTALL_QMLDIR}/org/kde/plasma/simplemenu")

install(TARGETS simplemenu DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/simplemenu)
install(FILES plugin/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/simplemenu)

plasma_install_package(package org.kde.plasma.simplemenu)
