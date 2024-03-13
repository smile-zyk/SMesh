#pragma once

#include "smesh/config/config.h"
#include "smesh/core.h"
#include <QHash>
#include <QString>
#include <QVariant>
#include <qlist.h>
#include <qvariant.h>

// config system based on QVariant

namespace smesh
{
    class PropertyDef;
    class ConfigDef;

    typedef QHash<QString, PropertyDef> PropertyDefMap;
    typedef QStringList PropertyKeyList;
    typedef QHash<QString, QVariant> PropertyMap;

    class SMESH_API PropertyDef
    {
      public:
        // for QHash initialize
        PropertyDef();
        PropertyDef(const PropertyDef& other) = default;
        PropertyDef(PropertyDef&& other) = default;
        explicit PropertyDef(QVariant::Type type) : type_(type) {}
        PropertyDef *AddSubProperty(const QString& key, QVariant::Type type);
        bool AddSubProperty(const QString& key, const PropertyDef& def);
        bool IsEqual(PropertyDef* other) const;
        bool IsKeyValid(const QString& key) const;
        QVariant::Type type() const { return type_; }
        QVariant default_value() const { return default_value_; }
        QVariant min() const { return min_; }
        QVariant max() const { return max_; }
        QString tool_tip() const { return tool_tip_; }
        void set_default_value(const QVariant& value) { default_value_ = value; }
        void set_min(const QVariant& min) { min_ = min; }
        void set_max(const QVariant& max) { max_ = max; }
        void set_tool_tip(const QString& tool_tip) { tool_tip_ = tool_tip; }
        const PropertyKeyList& sub_keys() const { return sub_property_key_list_; }
        PropertyDef* sub_property_def (const QString &key);
        const PropertyDef* sub_property_def (const QString &key) const;
      private:
        QVariant::Type type_{};
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
        ConfigDef() = default;
        ConfigDef(const ConfigDef &) = default;
        ConfigDef(ConfigDef&&) = default;
        bool IsEqual(ConfigDef* def) const;
        bool IsKeyValid(const QString& key) const;
        PropertyDef *AddProperty(const QString& key, QVariant::Type type);
        bool AddProperty(const QString& key, PropertyDef def);
        PropertyDef *property_def(const QString &key);
        const PropertyDef *property_def(const QString &key) const;
        const PropertyKeyList &keys() const { return property_key_list_; }
        PropertyKeyList all_keys();

      private:
        PropertyDefMap property_def_map_{};
        PropertyKeyList property_key_list_{};
        PropertyKeyList CombineKey(const QString& parent_key, PropertyDef* def);
      
      protected:
    };

    class SMESH_API Config
    {
      public:
        const PropertyKeyList& keys() { return def->keys(); }
        PropertyKeyList all_keys() const { return def->all_keys(); }
        bool IsEqual(const Config& other) const;
        bool IsKeyValid(const QString& key) const { return def->IsKeyValid(key); }
        PropertyKeyList diff_keys(const Config& other) const;
        PropertyDef *property_def(const QString &key) { return def->property_def(key); }
        const PropertyDef *property_def(const QString &key) const { return def->property_def(key); }
        QVariant property(const QString& key) const;
        bool set_property(const QString& key, QVariant value);
        bool WriteConfig(const QString &file_path) const;
        bool ReadConfig(const QString &file_path) const;

      private:
        ConfigDef *def;
        mutable PropertyMap config_map;
      protected:
        Config(ConfigDef *def);
    };
} // namespace smesh