#pragma once

#include "smesh/core.h"
#include <QHash>
#include <QString>
#include <QVariant>
#include <QtVariantPropertyManager>
#include <qvariant.h>

// config system based on QVariant

namespace smesh
{
    class PropertyDef;
    class ConfigDef;

    typedef int PropertyType;
    typedef QString PropertyKey;
    typedef QString AttributeKey;
    typedef QHash<PropertyKey, PropertyDef> PropertyDefMap;
    typedef QStringList PropertyKeyList;
    typedef QStringList AttributeList;
    typedef QHash<PropertyKey, QVariant> PropertyMap;
    typedef QHash<AttributeKey, QVariant> AttributeMap;

    class SMESH_API PropertyDef
    {
      public:
        // for QHash initialize
        PropertyDef();
        explicit PropertyDef(PropertyType type) : type_(type) {}
        PropertyDef *AddSubProperty(const PropertyKey &key, QVariant::Type type);
        bool AddSubProperty(const PropertyKey &key, const PropertyDef &def);
        bool IsValid() { return type_ != QVariant::Type::Invalid; }
        bool IsSubKeyValid(const PropertyKey &key) const;
        PropertyType type() const { return type_; }
        QVariant default_value() const { return default_value_; }
        void set_default_value(const QVariant &value) { default_value_ = value; }
        QString tool_tip() const { return tool_tip_; }
        void set_tool_tip(const QString& tool_tip) { tool_tip_ = tool_tip; }
        bool read_only() const { return read_only_; }
        void set_read_only(bool read_only) { read_only_ = read_only; }
        void set_attribute_value(const AttributeKey &attribute, const QVariant &value) { attribute_map_.insert(attribute, value); }
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
        AttributeMap attribute_map_{};
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

      private:
        PropertyDefMap property_def_map_{};
        PropertyKeyList property_key_list_{};
        PropertyKeyList CombineKey(const QString &parent_key, const PropertyDef *def) const;

      protected:
        ConfigDef() {}
        PropertyDef *AddProperty(const PropertyKey &key, int type);
        bool AddProperty(const PropertyKey &key, PropertyDef def);
    };

    class SMESH_API Config
    {
      public:
        const PropertyKeyList &keys() { return def_->keys(); }
        PropertyKeyList all_keys() const { return def_->all_keys(); }
        bool IsEqual(const Config &other) const;
        bool IsKeyValid(const PropertyKey &key) const { return def_->IsKeyValid(key); }
        PropertyKeyList diff_keys(const Config &other) const;
        // PropertyDef *property_def(const PropertyKey &key) { return def_->property_def(key); }
        const PropertyDef *property_def(const PropertyKey &key) const { return def_->property_def(key); }
        QVariant property(const PropertyKey &key) const;
        bool set_property(const PropertyKey &key, QVariant value);
        // bool WriteConfig(const QString &file_path) const;
        // bool ReadConfig(const QString &file_path) const;

      private:
        // Config can't modify def
        const ConfigDef *def_;
        mutable PropertyMap config_map_;
      protected:
        Config(const ConfigDef *def) : def_(def) {}
    };
} // namespace smesh