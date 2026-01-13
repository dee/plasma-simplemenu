cmake_minimum_required(VERSION 3.16)

project(plasma-simplemenu)

set(QT_DEFAULT_MAJOR_VERSION 6)
set(QT_NO_CREATE_VERSIONLESS_TARGETS TRUE)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

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
#    plugin/simplemenu.cpp
#    plugin/simplemenu.h
    package/plugin/plugin.cpp
)

target_link_libraries(simplemenu
    Qt6::Core
    Qt6::Quick
    Qt6::Widgets
    KF6::Service
    KF6::I18n
    Plasma::Plasma
    Plasma::PlasmaQuick
)

# Установка
install(TARGETS simplemenu DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/simplemenu)
install(FILES plugin/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/simplemenu)

# Установка плазмоида
plasma_install_package(package org.kde.plasma.simplemenu)
