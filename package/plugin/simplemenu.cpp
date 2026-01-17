
#include "simplemenu.h"

SimpleMenu::SimpleMenu(QObject* parent)
    : QAbstractListModel(parent),
    m_filteredApps(),
    m_apps()
{

}

int SimpleMenu::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_filteredApps.size();
}

QVariant SimpleMenu::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredApps.size()) {
        return QVariant();
    }

    const AppItem &app = m_filteredApps.at(index.row());

    switch (role) {
    case NameRole:
        return app.name;
    case IconRole:
        return app.icon;
    case ExecRole:
        return app.exec;
    case DescriptionRole:
        return app.description;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SimpleMenu::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[ExecRole] = "exec";
    roles[DescriptionRole] = "description";
    return roles;
}
