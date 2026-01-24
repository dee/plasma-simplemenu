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

class SimpleMenuListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        ExecRole,
        DescriptionRole
    };

    SimpleMenuListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void loadApplications();

    QString filter() const;
    void setFilter(const QString &);

    Q_INVOKABLE void launchApp(int index);

private:
    QString m_filter;
    QList<AppItem> m_filteredApps, m_apps;

    void updateFilteredList();
};

class SimpleMenu : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString filter READ filter WRITE setFilter)
    Q_PROPERTY(SimpleMenuListModel* model READ model)

public:
    static SimpleMenu *create(QQmlEngine *, QJSEngine *);

    QString filter() const { return m_model.filter(); }
    SimpleMenuListModel* model() { return &m_model; }

    void setFilter(const QString& value) { m_model.setFilter(value); }

private:
    SimpleMenuListModel m_model;

    SimpleMenu();
};
