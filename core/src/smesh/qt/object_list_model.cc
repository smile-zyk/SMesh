#include "object_list_model.h"
#include <qnamespace.h>

ObjectListModel::ObjectListModel(smesh::Renderer *renderer, QObject *parent) : QAbstractListModel(parent)
{
    renderer_ = renderer;
}

int ObjectListModel::rowCount(const QModelIndex &parent) const 
{
    return static_cast<int>(renderer_->object_count());
}

QVariant ObjectListModel::data(const QModelIndex &index, int role) const 
{
    if (!index.isValid())
        return {};
    const int row = index.row();
    if (row >= rowCount() || row < 0)
        return {};

    switch (role) {
        case Qt::DisplayRole:
        return QString::fromStdString(renderer_->object(row)->name());
    }
    return {};
}

void ObjectListModel::UpdateAll()
{
    QModelIndex first = createIndex(0,0);
    QModelIndex last = createIndex(rowCount() - 1, 0);
    emit dataChanged(first, last);
}

void ObjectListModel::UpdateObject(int row)
{
    if (row >= rowCount() || row < 0)
        return;
    QModelIndex idx = createIndex(row, 0);
    emit dataChanged(idx, idx);
}


