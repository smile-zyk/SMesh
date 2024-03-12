#include "config.h"

namespace smesh
{
    ConfigOptionDef* Config::AddConfigDefinition(const QString& key, QVariant::Type type)
    {
        config_def_map_.insert(key, ConfigOptionDef(type, key));
        config_map_.insert(key, QVariant());
        keys_.push_back(key);
        return &config_def_map_[key];
    }

    ConfigOptionDef* Config::GetConfigDefinition(const QString& key)
    {
        if(config_def_map_.contains(key) == false) return nullptr;
        return &config_def_map_[key];
    }

    QVariant Config::GetConfig(const QString& key)
    {
        if(config_def_map_.contains(key) == false || config_map_.contains(key) == false) return QVariant();
        if(config_map_[key].isValid() == false && config_def_map_[key].default_value().isValid() != false)
        {
            config_map_[key] = config_def_map_[key].default_value();
        }
        return config_map_[key];
    }

    bool Config::WriteConfig(const QString& file_path)
    {
        return false;
    }

    bool Config::ReadConfig(const QString& file_path)
    {
        return false;
    }
}