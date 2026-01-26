#include "simplemenu.h"

#include <QStringLiteral>
#include <KService>
#include <QProcess>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

SimpleMenu *SimpleMenu::create(QQmlEngine *, QJSEngine *)
{
    static SimpleMenu instance;
    QQmlEngine::setObjectOwnership(&instance, QQmlEngine::CppOwnership);
    return &instance;
}

SimpleMenu::SimpleMenu()
    : QObject(nullptr)
    , m_model()
{}

SimpleMenuListModel::SimpleMenuListModel()
    : QAbstractListModel(nullptr),
    m_filteredApps(),
    m_apps()
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
        // qDebug() << "Found:" << service->name();
        if (service->noDisplay() || !service->isApplication() || service->exec().isEmpty() || service->name().isEmpty())
        {
            // qDebug() << "Skipping" << service->name();
            continue;
        }

        AppItem item;
        item.name = service->name();
        item.exec = service->exec();
        item.icon = service->icon();
        item.description = service->comment();
        m_apps.append(item);

        // qDebug() << "Added item:" << item.name << "(" << item.exec << ")";
    }

    updateFilteredList();
}

QString SimpleMenuListModel::filter() const
{
    return m_filter;
}

void SimpleMenuListModel::setFilter(const QString &value)
{
    m_filter = value;
    updateFilteredList();
}

void SimpleMenuListModel::updateFilteredList()
{
    beginResetModel();

    if (m_filter.isEmpty())
    {
        m_filteredApps = m_apps;
    }
    else
    {
        m_filteredApps.clear();
        const QString filter = m_filter.toLower();

        for (const AppItem &app : std::as_const(m_apps))
        {
            //TODO: case-insensitivity
            if (app.name.toLower().contains(filter) ||
                app.description.toLower().contains(filter))
            {
                qDebug() << "Matching filter, adding:" << app.name;
                m_filteredApps.append(app);
            }
        }
    }

    std::sort(m_filteredApps.begin(), m_filteredApps.end(),
    [](const AppItem &a, const AppItem &b)
    {
        return QString::localeAwareCompare(a.name, b.name) < 0;
    });

    endResetModel();
}

void SimpleMenuListModel::launchApp(int index)
{
    if (index < 0 || index >= m_filteredApps.size())
    {
        return;
    }

    const AppItem &app = m_filteredApps.at(index);

    QStringList args = app.exec.split(u' ', Qt::SkipEmptyParts);
    if (!args.isEmpty())
    {
        QString program = args.takeFirst();
        QProcess::startDetached(program, args);
    }
}

void SimpleMenu::logout()
{
    QDBusInterface interface(QStringLiteral("org.kde.Shutdown"),
                             QStringLiteral("/Shutdown"),
                             QStringLiteral("org.kde.Shutdown"),
                             QDBusConnection::sessionBus());
    if (!interface.isValid())
    {
        qWarning() << "Interface is not valid!";
        return;
    }
    qDebug() << "Calling logout";
    QDBusReply<void> reply = interface.call(QStringLiteral("logout"));
    if (!reply.isValid()) {
        qDebug() << "DBus call failed:" << reply.error().message();
    }
}

void SimpleMenu::poweroff()
{
    QDBusInterface interface(QStringLiteral("org.kde.Shutdown"),
                             QStringLiteral("/Shutdown"),
                             QStringLiteral("org.kde.Shutdown"),
                             QDBusConnection::sessionBus());
    if (!interface.isValid())
    {
        qWarning() << "Interface is not valid!";
        return;
    }
    qDebug() << "Calling logoutAndShutdown";
    QDBusReply<void> reply = interface.call(QStringLiteral("logoutAndShutdown"));
    if (!reply.isValid()) {
        qDebug() << "DBus call failed:" << reply.error().message();
    }
}
