plasma_add_applet(simplemenu
    QML_SOURCES
        qml/main.qml
    CPP_SOURCES
        simplemenu.cpp
#    RESOURCES
#        qml/images/pairs.svg
    GENERATE_APPLET_CLASS
)

target_link_libraries(simplemenu PRIVATE
    Qt6::Gui
    Plasma::Plasma
    KF6::I18n
)
