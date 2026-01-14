#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QModelIndex>
#include <QByteArray>


class SimpleMenu : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SimpleMenu(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<QString> m_filteredApps;
};
