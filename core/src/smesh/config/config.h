#pragma once

#include "smesh/core.h"
#include <QMap>
#include <QString>
#include <QVariant>
#include <QtVariantPropertyManager>
#include <QObject>
#include <functional>
#include <qvariant.h>

// config system based on QVariant

namespace smesh
{
    class PropertyDef;
    class ConfigDef;

    typedef int PropertyType;
    typedef QString PropertyKey;
    typedef QString AttributeKey;
    typedef QMap<PropertyKey, PropertyDef> PropertyDefMap;
    typedef QStringList PropertyKeyList;
    typedef QStringList AttributeList;
    typedef QMap<PropertyKey, QVariant> PropertyMap;
    typedef QMap<AttributeKey, QVariant> AttributeMap;
    struct Condition
    {
      QVariantList trigger_values{};
      QStringList trigger_keys{};
      std::function<void()> trigger_func{};
    };
    typedef QList<Condition> ConditionList;

    class SMESH_API PropertyDef
    {
      public:
        PropertyDef();
        explicit PropertyDef(PropertyType type);
        PropertyDef *AddSubProperty(const PropertyKey &key, int type);
        bool IsValid() { return type_ != QVariant::Type::Invalid; }
        bool IsSubKeyValid(const PropertyKey &key) const;
        PropertyType type() const { return type_; }
        QVariant default_value() const { return default_value_; }
        void set_default_value(const QVariant &value) { default_value_ = value; }
        QString tool_tip() const { return tool_tip_; }
        void set_tool_tip(const QString& tool_tip) { tool_tip_ = tool_tip; }
        bool read_only() const { return read_only_; }
        void set_read_only(bool read_only) { read_only_ = read_only; }
        bool enable() const { return enable_; }
        void set_enable(bool enable) { enable_ = enable; }
        bool visible() const { return visible_; }
        void set_visible(bool visible) { visible_ = visible; } 
        void set_attribute_value(const AttributeKey &attribute, const QVariant &value) { attribute_map_.insert(attribute, value); }
        void add_condition(const QVariantList& values, const QStringList& property_keys, std::function<void()> condition_func) { condition_list_.push_back({values, property_keys, condition_func}); }
        ConditionList condition() const { return condition_list_; }
        QVariant attribute_value(const AttributeKey &attribute) const;
        AttributeList attributes() const { return attribute_map_.keys(); }
        const PropertyKeyList &sub_keys() const { return sub_property_key_list_; }
        PropertyDef *sub_property_def(const PropertyKey &key);
        const PropertyDef *sub_property_def(const PropertyKey &key) const;

      private:
        PropertyType type_{};
        QVariant default_value_{};
        QString tool_tip_{};
        bool read_only_{};
        bool enable_{true};
        bool visible_{true};
        AttributeMap attribute_map_{};
        ConditionList condition_list_{};
        PropertyDefMap sub_property_def_map_{};
        PropertyKeyList sub_property_key_list_{};
    };

    class SMESH_API ConfigDef
    {
      public:
        bool IsKeyValid(const QString &key) const;
        PropertyDef *property_def(const PropertyKey &key);
        const PropertyDef *property_def(const PropertyKey &key) const;
        const PropertyKeyList &keys() const { return property_key_list_; }
        PropertyKeyList all_keys() const;
        virtual QString ConfigDefName() const;

      private:
        PropertyDefMap property_def_map_{};
        PropertyKeyList property_key_list_{};
        PropertyKeyList CombineKey(const QString &parent_key, const PropertyDef *def) const;

      protected:
        ConfigDef() {}
        PropertyDef *AddProperty(const PropertyKey &key, int type);
    };


    class SMESH_API Config : public QObject
    {
      Q_OBJECT
      public:
        const PropertyKeyList &keys() { return def_->keys(); }
        PropertyKeyList all_keys() const { return def_->all_keys(); }
        bool IsEqual(const Config &other) const;
        bool IsKeyValid(const PropertyKey &key) const { return def_->IsKeyValid(key); }
        PropertyKeyList diff_keys(const Config &other) const;
        // PropertyDef *property_def(const PropertyKey &key) { return def_->property_def(key); }
        const PropertyDef *property_def(const PropertyKey &key) const { return def_->property_def(key); }
        const ConfigDef* def() const { return def_; }
        QVariant property(const PropertyKey &key) const;
        bool set_property(const PropertyKey &key, QVariant value, bool is_triggered = false);
        // bool WriteConfig(const QString &file_path) const;
        // bool ReadConfig(const QString &file_path) const;

      signals:
        void propertyChanged(const PropertyKey& key, QVariant value);
        void triggeredPropertyChanged(const PropertyKey& key, QVariant value, QVariant old_value);

      private:
        // Config can't modify def
        const ConfigDef *def_;
        mutable PropertyMap config_map_;

      protected:
        Config(const ConfigDef *def) : def_(def) {}
    };
} // namespace smesh