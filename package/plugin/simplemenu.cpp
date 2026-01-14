
#include "simplemenu.h"

SimpleMenu::SimpleMenu(QObject* parent)
    : QAbstractListModel(parent),
    m_filteredApps()
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

    const QVariant &app = m_filteredApps.at(index.row());

    return app;
}

QHash<int, QByteArray> SimpleMenu::roleNames() const
{
    QHash<int, QByteArray> roles{};
    return roles;
}
