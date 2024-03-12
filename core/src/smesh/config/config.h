#pragma once

#include "smesh/config/config.h"
#include "smesh/core.h"
#include <QHash>
#include <QString>
#include <QVariant>
#include <qvariant.h>


// config system based on QVariant

namespace smesh
{
    class SMESH_API ConfigOptionDef
    {
      public:
        ConfigOptionDef() {}
        explicit ConfigOptionDef(QVariant::Type type, QVariant value) : type_(type), default_value_(value) {}
        QVariant::Type type() { return type_; }
        QVariant default_value() { return default_value_; }
        QVariant min() { return min_; }
        QVariant max() { return max_; }
        QString side_text() { return side_text_; }
        QString tool_tip() { return tool_tip_; }
        void set_default_value(QVariant value) { default_value_ = value; }
        void set_min(QVariant min) { min_ = min; }
        void set_max(QVariant max) { max_ = max; }
        void set_side_text(QString side_text) { side_text_ = side_text; }
        void set_tool_tip(QString tool_tip) { tool_tip_ = tool_tip; }

      private:
        QVariant::Type type_{};
        QVariant default_value_{};
        QVariant min_{};
        QVariant max_{};
        QString side_text_{};
        QString tool_tip_{};

      protected:
    };

    typedef QHash<QString, ConfigOptionDef> ConfigDefKeyMap;
    typedef QHash<QString, QVariant> ConfigKeyMap;

    class SMESH_API Config
    {
      public:
        ConfigOptionDef* AddConfigDefinition(const QString &key, QVariant::Type type);
        QStringList &keys() { return keys_; }
        ConfigOptionDef *GetConfigDefinition(const QString &key);
        QVariant GetConfig(const QString &key);
        bool WriteConfig(const QString &file_path);
        bool ReadConfig(const QString &file_path);

      private:
        ConfigDefKeyMap config_def_map_;
        ConfigKeyMap config_map_;
        QStringList keys_;
    };
} // namespace smesh