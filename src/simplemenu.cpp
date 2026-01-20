#include "simplemenu.h"

#include <QStringLiteral>

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
}
