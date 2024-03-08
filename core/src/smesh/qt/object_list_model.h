#pragma once
#include <QAbstractListModel>
#include <QStringListModel>
#include "smesh/core.h"
#include "smesh/render/renderer.h"

class SMESH_API ObjectListModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    explicit ObjectListModel(smesh::Renderer *renderer, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void UpdateAll();
    void UpdateObject(int row);
  private:
    smesh::Renderer *renderer_;
};