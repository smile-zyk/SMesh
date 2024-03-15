#pragma once

#include "qtpropertymanager.h"
#include "qtvectorproperty.h"
#include <QVector3D>
#include <QScopedPointer>

class QtVector3DPropertyManagerPrivate;

class QtVector3DPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
  public:
    QtVector3DPropertyManager(QObject *parent = nullptr);
    ~QtVector3DPropertyManager();

    QtDoublePropertyManager *subDoublePropertyManager() const;

    QVector3D value(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

    void setValue(QtProperty *property, const QVector3D &val);
    void setDecimals(QtProperty *property, int prec);

  signals:
    void valueChanged(QtProperty *property, const QPointF &val);
    void decimalsChanged(QtProperty *property, int prec);

  protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);

  private:
    QScopedPointer<QtVector3DPropertyManagerPrivate> d_ptr;
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QtProperty *))

    Q_DECLARE_PRIVATE(QtVector3DPropertyManager)
    Q_DISABLE_COPY_MOVE(QtVector3DPropertyManager)
};