#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QModelIndex>
#include <QByteArray>
#include <QString>

struct AppItem {
    QString name;
    QString exec;
    QString icon;
    QString description;
};

class SimpleMenu : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        ExecRole,
        DescriptionRole
    };

    explicit SimpleMenu(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<AppItem> m_filteredApps, m_apps;
};
