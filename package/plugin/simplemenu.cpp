#include <KService>
#include <QDebug>

#include "simplemenu.h"

SimpleMenu::SimpleMenu(QObject* parent)
    : QAbstractListModel(parent),
    m_filteredApps(),
    m_apps()
{
    loadApplications();
}

int SimpleMenu::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_filteredApps.size();
}

QVariant SimpleMenu::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredApps.size())
    {
        return QVariant();
    }

    const AppItem &app = m_filteredApps.at(index.row());

    switch (role)
    {
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

void SimpleMenu::loadApplications()
{
    m_apps.clear();

    const KService::List services = KService::allServices();

    for (const KService::Ptr &service : services)
    {
        if (service->noDisplay() || !service->isApplication())
        {
            qDebug() << "Skipping" << service->name();
            continue;
        }

        AppItem item;
        item.name = service->name();
        item.exec = service->exec();
        item.icon = service->icon();
        item.description = service->comment();

        if (item.name.isEmpty() || item.exec.isEmpty())
        {
            continue;
        }

        m_apps.append(item);
        m_filteredApps.append(item); //TODO: implement filter
    }

    std::sort(m_apps.begin(), m_apps.end(), [](const AppItem &a, const AppItem &b)
    {
      return QString::localeAwareCompare(a.name, b.name) < 0;
    });
}
