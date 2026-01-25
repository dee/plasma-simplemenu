plasma_add_applet(org.kde.plasma.simplemenu
    QML_SOURCES
        qml/main.qml
    CPP_SOURCES
        simplemenu.cpp
#    RESOURCES
#        qml/images/pairs.svg
    GENERATE_APPLET_CLASS
)

target_link_libraries(org.kde.plasma.simplemenu PRIVATE
    Qt6::Gui
    Plasma::Plasma
    KF6::I18n
    KF6::Service
    Qt6::DBus
)
