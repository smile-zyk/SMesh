#include "qtvectorproperty.h"
#include "qtpropertybrowser.h"
#include <QMap>
#include <qglobal.h>

class QtVector3DPropertyManagerPrivate
{
    QtVector3DPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtVector3DPropertyManager)
  public:
    struct Data
    {
        QVector3D val;
        int decimals{2};
    };

    void slotDoubleChanged(QtProperty *property, double value);
    void slotPropertyDestroyed(QtProperty *property);

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToX;
    QMap<const QtProperty *, QtProperty *> m_propertyToY;
    QMap<const QtProperty *, QtProperty *> m_propertyToZ;

    QMap<const QtProperty *, QtProperty *> m_xToProperty;
    QMap<const QtProperty *, QtProperty *> m_yToProperty;
    QMap<const QtProperty *, QtProperty *> m_zToProperty;
};

void QtVector3DPropertyManagerPrivate::slotDoubleChanged(QtProperty *property, double value)
{
    if (QtProperty *prop = m_xToProperty.value(property, 0))
    {
        QVector3D p = m_values[prop].val;
        p.setX(value);
        q_ptr->setValue(prop, p);
    }
    else if (QtProperty *prop = m_yToProperty.value(property, 0))
    {
        QVector3D p = m_values[prop].val;
        p.setY(value);
        q_ptr->setValue(prop, p);
    }
    else if (QtProperty *prop = m_zToProperty.value(property, 0))
    {
        QVector3D p = m_values[prop].val;
        p.setZ(value);
        q_ptr->setValue(prop, p);
    }
}

void QtVector3DPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_xToProperty.value(property, 0))
    {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    }
    else if (QtProperty *pointProp = m_yToProperty.value(property, 0))
    {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    }
    else if (QtProperty *pointProp = m_zToProperty.value(property, 0))
    {
        m_propertyToZ[pointProp] = 0;
        m_zToProperty.remove(property);
    }
}

QtVector3DPropertyManager::QtVector3DPropertyManager(QObject* parent): QtAbstractPropertyManager(parent), d_ptr(new QtVector3DPropertyManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QtDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QtProperty*,double)),
                this, SLOT(slotDoubleChanged(QtProperty*,double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QtProperty*)),
                this, SLOT(slotPropertyDestroyed(QtProperty*)));
}

QtVector3DPropertyManager::~QtVector3DPropertyManager()
{
    clear();
}

QtDoublePropertyManager* QtVector3DPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QVector3D QtVector3DPropertyManager::value(const QtProperty* property) const
{
    const auto it = d_ptr->m_values.constFind(property);
    if(it == d_ptr->m_values.constEnd())
    {
        return QVector3D();   
    }
    return it.value().val;
}

int QtVector3DPropertyManager::decimals(const QtProperty *property) const
{
    return 0;
}

void QtVector3DPropertyManager::setValue(QtProperty *property, const QVector3D &val)
{
    
}

void QtVector3DPropertyManager::setDecimals(QtProperty *property, int prec)
{
    
}

QString QtVector3DPropertyManager::valueText(const QtProperty *property) const
{
    return "";
}

void QtVector3DPropertyManager::initializeProperty(QtProperty *property)
{
    
}

void QtVector3DPropertyManager::uninitializeProperty(QtProperty *property)
{
    
}

#include "moc_qtvectorproperty.cpp"
