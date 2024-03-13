#pragma once

#include "smesh/core.h"
#include <QHash>
#include <QString>
#include <QVariant>
#include <QtVariantPropertyManager>

// config system based on QVariant

namespace smesh
{
    class PropertyDef;
    class ConfigDef;

    typedef int PropertyType;
    typedef QString PropertyKey;
    typedef QHash<PropertyKey, PropertyDef> PropertyDefMap;
    typedef QStringList PropertyKeyList;
    typedef QHash<PropertyKey, QVariant> PropertyMap;

    class SMESH_API PropertyDef
    {
      public:
        // for QHash initialize
        PropertyDef();
        explicit PropertyDef(PropertyType type) : type_(type) {}
        PropertyDef *AddSubProperty(const PropertyKey& key, QVariant::Type type);
        bool AddSubProperty(const PropertyKey& key, const PropertyDef& def);
        bool IsValid() { return type_ != QVariant::Type::Invalid; }
        bool IsEqual(PropertyDef* other) const;
        bool IsSubKeyValid(const PropertyKey& key) const;
        PropertyType type() const { return type_; }
        QVariant default_value() const { return default_value_; }
        QVariant min() const { return min_; }
        QVariant max() const { return max_; }
        QString tool_tip() const { return tool_tip_; }
        void set_default_value(const QVariant& value) { default_value_ = value; }
        void set_min(const QVariant& min) { min_ = min; }
        void set_max(const QVariant& max) { max_ = max; }
        void set_tool_tip(const QString& tool_tip) { tool_tip_ = tool_tip; }
        const PropertyKeyList& sub_keys() const { return sub_property_key_list_; }
        PropertyDef* sub_property_def (const PropertyKey &key);
        const PropertyDef* sub_property_def (const PropertyKey &key) const;
      private:
        PropertyType type_{};
        QVariant default_value_{};
        QVariant min_{};
        QVariant max_{};
        QString tool_tip_{};
        PropertyDefMap sub_property_def_map_{};
        PropertyKeyList sub_property_key_list_{};
    };

    class SMESH_API ConfigDef
    {
      public:
        bool IsEqual(ConfigDef* def) const;
        bool IsKeyValid(const QString& key) const;
        PropertyDef *AddProperty(const PropertyKey& key, QVariant::Type type);
        bool AddProperty(const PropertyKey& key, PropertyDef def);
        PropertyDef *property_def(const PropertyKey &key);
        const PropertyDef *property_def(const PropertyKey &key) const;
        const PropertyKeyList &keys() const { return property_key_list_; }
        PropertyKeyList all_keys();

      private:
        PropertyDefMap property_def_map_{};
        PropertyKeyList property_key_list_{};
        PropertyKeyList CombineKey(const QString& parent_key, PropertyDef* def);
    };

    class SMESH_API Config
    {
      public:
        Config(ConfigDef *def): def_(def){}
        const PropertyKeyList& keys() { return def_->keys(); }
        PropertyKeyList all_keys() const { return def_->all_keys(); }
        bool IsEqual(const Config& other) const;
        bool IsKeyValid(const PropertyKey& key) const { return def_->IsKeyValid(key); }
        PropertyKeyList diff_keys(const Config& other) const;
        PropertyDef *property_def(const PropertyKey &key) { return def_->property_def(key); }
        const PropertyDef *property_def(const PropertyKey &key) const { return def_->property_def(key); }
        QVariant property(const PropertyKey& key) const;
        bool set_property(const PropertyKey& key, QVariant value);
        bool WriteConfig(const QString &file_path) const;
        bool ReadConfig(const QString &file_path) const;

      private:
        ConfigDef *def_;
        mutable PropertyMap config_map_;

    };
} // namespace smesh