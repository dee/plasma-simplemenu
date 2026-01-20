#pragma once

#include <QObject>
#include <QString>
#include <QQmlEngine>
#include <QAbstractListModel>

struct AppItem {
    QString name;
    QString exec;
    QString icon;
    QString description;
};

class SimpleMenuListModel : QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        ExecRole,
        DescriptionRole
    };

    SimpleMenuListModel(QObject* parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void loadApplications();

private:
    QList<AppItem> m_filteredApps, m_apps;

};

class SimpleMenu : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString message READ message CONSTANT)

public:
    static SimpleMenu *create(QQmlEngine *, QJSEngine *);

    QString message() const;

private:
    SimpleMenuListModel m_model;

    SimpleMenu();
};


