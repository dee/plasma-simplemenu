#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QModelIndex>
#include <QByteArray>
#include <QString>
#include <QQmlEngine>

struct AppItem {
    QString name;
    QString exec;
    QString icon;
    QString description;
};

class SimpleMenu : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        ExecRole,
        DescriptionRole
    };

    static HelloWorld *create(QQmlEngine *, QJSEngine *);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void loadApplications();

private:
    QList<AppItem> m_filteredApps, m_apps;

    explicit SimpleMenu(QObject* parent = nullptr);
};

