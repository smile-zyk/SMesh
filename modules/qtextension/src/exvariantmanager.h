#pragma once
#include "qtvariantproperty.h"
#include <qvariant.h>

class ExVariantManager : public QtVariantPropertyManager
{
 Q_OBJECT
 public:
    ExVariantManager(QObject* parent = nullptr);
    ~ExVariantManager();

    virtual QVariant value(const QtProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;

    virtual void setValue(QtProperty *property, const QVariant &val);
 protected:
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void slotPropertyDestroyed(QtProperty *property);
};