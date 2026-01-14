#include <QtQml>
#include <QQmlExtensionPlugin>
#include "simplemenu.h"


class SimpleMenuPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char* uri) override
    {
        qmlRegisterType<SimpleMenu>(uri, 1, 0, "SimpleMenu");
    }
};

#include "plugin.moc"
