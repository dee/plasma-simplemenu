#include "simplemenu.h"

#include <QStringLiteral>
#include <KService>

QString SimpleMenu::message() const
{
    return QStringLiteral("Hello!");
}

SimpleMenu *SimpleMenu::create(QQmlEngine *, QJSEngine *)
{
    static SimpleMenu instance;
    QQmlEngine::setObjectOwnership(&instance, QQmlEngine::CppOwnership);
    return &instance;
}

SimpleMenu::SimpleMenu()
    : QObject(nullptr)
    ,m_model(nullptr)
{}

SimpleMenuListModel::SimpleMenuListModel(QObject *parent)
{
    loadApplications();
}

int SimpleMenuListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_filteredApps.size();
}

QVariant SimpleMenuListModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> SimpleMenuListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[ExecRole] = "exec";
    roles[DescriptionRole] = "description";
    return roles;
}

void SimpleMenuListModel::loadApplications()
{
    m_apps.clear();

    const KService::List services = KService::allServices();

    for (const KService::Ptr &service : services)
    {
        qDebug() << "Found:" << service->name();
        if (service->noDisplay() || !service->isApplication() || service->exec().isEmpty() || service->name().isEmpty())
        {
            qDebug() << "Skipping" << service->name();
            continue;
        }

        AppItem item;
        item.name = service->name();
        item.exec = service->exec();
        item.icon = service->icon();
        item.description = service->comment();
        m_apps.append(item);
        m_filteredApps.append(item); //TODO: implement filter

        qDebug() << "Added item:" << item.name << "(" << item.exec << ")";
    }

    std::sort(m_apps.begin(), m_apps.end(), [](const AppItem &a, const AppItem &b)
              {
                  return QString::localeAwareCompare(a.name, b.name) < 0;
              });
}
