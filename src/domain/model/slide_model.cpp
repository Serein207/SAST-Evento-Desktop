#include "slide_model.h"

SlideModel::SlideModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int SlideModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant SlideModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::Link:
        return element.link;
    case Role::Url:
        return element.url;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> SlideModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Link, "link");
        roles.insert(Url, "url");
    }
    return roles;
}

void SlideModel::resetModel(const std::vector<Slide> &model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}
