#include "config.h"
#include "smesh/config/config.h"
#include <qvariant.h>

namespace smesh
{
    PropertyDef::PropertyDef(): type_(QVariant::Type::Invalid)
    {
    }

    PropertyDef* PropertyDef::AddSubProperty(const PropertyKey& key, QVariant::Type type)
    {
        if(type == QVariant::Type::Invalid) return nullptr;
        if(sub_property_def_map_.contains(key) == true) return nullptr;

        sub_property_def_map_.insert(key, PropertyDef(type));
        sub_property_key_list_.push_back(key);
        return &sub_property_def_map_[key];
    }

    bool PropertyDef::AddSubProperty(const PropertyKey& key, const PropertyDef& def)
    {
        if(def.type() == QVariant::Type::Invalid) return false;
        if(sub_property_def_map_.contains(key) == true) return false;

        sub_property_def_map_.insert(key, def);
        sub_property_key_list_.push_back(key);
        return true;
    }
    
    bool PropertyDef::IsSubKeyValid(const PropertyKey& key) const
    {
        QStringList parts = key.split('/');
        if(parts.count() == 0) return false;
        else if(parts.count() == 1)
        { 
            if(sub_property_key_list_.contains(parts[0]) == false)
                return false;
            else
                return true;
        }
        else 
        {
            QString head = parts[0];
            QString remain = key.mid(head.size() + 1);
            return sub_property_def(head)->IsSubKeyValid(remain);
        }
    }
    
    QVariant PropertyDef::attribute_value(const AttributeKey& attribute) const
    {
        if(attribute_map_.contains(attribute) == false)
            return QVariant();
        return attribute_map_[attribute];
    }

    PropertyDef* PropertyDef::sub_property_def(const PropertyKey &key)
    {
        QStringList parts = key.split('/');
        if(parts.count() == 0) return nullptr;
        else if(parts.count() == 1)
        {
            auto t = sub_property_def_map_[parts[0]];
            if(sub_property_key_list_.contains(parts[0]) == false)
                return nullptr;
            else
                return &sub_property_def_map_[parts[0]];
        }
        else 
        {
            QString head = parts[0];
            QString remain = key.mid(head.size() + 1);
            return sub_property_def(head)->sub_property_def(remain);
        }
    }
    
    const PropertyDef* PropertyDef::sub_property_def(const PropertyKey &key) const
    {
        QStringList parts = key.split('/');
        if(parts.count() == 0) return nullptr;
        else if(parts.count() == 1)
        {
            auto t = sub_property_def_map_[parts[0]];
            if(sub_property_key_list_.contains(parts[0]) == false)
                return nullptr;
            else
                return &*sub_property_def_map_.constFind(key);
        }
        else 
        {
            QString head = parts[0];
            QString remain = key.mid(head.size() + 1);
            return sub_property_def(head)->sub_property_def(remain);
        }
    }
    
    bool ConfigDef::IsKeyValid(const PropertyKey& key) const
    {
        QStringList parts = key.split('/');
        if(parts.count() == 0) return false;
        else if(parts.count() == 1)
        { 
            if(property_key_list_.contains(parts[0]) == false)
                return false;
            else
                return true;
        }
        else 
        {
            QString head = parts[0];
            QString remain = key.mid(head.size() + 1);
            return property_def(head)->IsSubKeyValid(remain);
        }
    }
    
    PropertyDef* ConfigDef::AddProperty(const PropertyKey& key, int type)
    {
        if(type == QVariant::Type::Invalid) return nullptr;
        if(property_def_map_.contains(key) == true) return nullptr;

        property_def_map_.insert(key, PropertyDef(type));
        property_key_list_.push_back(key);
        return &property_def_map_[key];
    }
    
    bool ConfigDef::AddProperty(const PropertyKey& key, PropertyDef def)
    {
        if(def.type() == QVariant::Type::Invalid) return false;
        if(property_def_map_.contains(key) == true) return false;

        property_def_map_.insert(key, def);
        property_key_list_.push_back(key);
        return true;
    }
    
    PropertyDef* ConfigDef::property_def(const PropertyKey &key)
    {
        QStringList parts = key.split('/');
        if(parts.count() == 0) return nullptr;
        else if(parts.count() == 1)
        { 
            if(property_key_list_.contains(parts[0]) == false)
                return nullptr;
            else
                return &property_def_map_[parts[0]];
        }
        else 
        {
            QString head = parts[0];
            QString remain = key.mid(head.size() + 1);
            return property_def(head)->sub_property_def(remain);
        }
    }
    
    const PropertyDef* ConfigDef::property_def(const PropertyKey &key) const
    {
        QStringList parts = key.split('/');
        if(parts.count() == 0) return nullptr;
        else if(parts.count() == 1)
        { 
            if(property_key_list_.contains(parts[0]) == false)
                return nullptr;
            else
                return &*property_def_map_.constFind(key);
        }
        else 
        {
            QString head = parts[0];
            QString remain = key.mid(head.size() + 1);
            return property_def(head)->sub_property_def(remain);
        }
    }
    
    PropertyKeyList ConfigDef::all_keys() const
    {
        PropertyKeyList res;
        auto& self_keys = keys();
        for(auto &key : self_keys)
        {
            res.push_back(key);
            res.append(CombineKey(key, property_def(key)));
        }
        return res;
    }
    
    bool Config::IsEqual(const Config& other) const
    {
        return diff_keys(other).isEmpty();
    }
    
    PropertyKeyList Config::diff_keys(const Config& other) const
    {
        PropertyKeyList keys = all_keys();
        PropertyKeyList diff;
        for(auto& key: keys)
        {
            if(other.IsKeyValid(key) && property(key) != other.property(key))
                diff.push_back(key);
        }
        return diff;
    }
    
    QVariant Config::property(const PropertyKey &key) const
    {
        if(IsKeyValid(key))
        {
            if(config_map_.contains(key) == false)
            {
                config_map_[key] = property_def(key)->default_value();
            }
            return config_map_[key];
        }
        else 
            return QVariant();
    }
    
    bool Config::set_property(const QString& key, QVariant value)
    {
        if(IsKeyValid(key))
        {
            config_map_[key] = value;
            return true;
        }
        else
            return false;
    }
    
    PropertyKeyList ConfigDef::CombineKey(const QString& parent_key, const PropertyDef* def) const
    {
        PropertyKeyList res;
        auto& keys = def->sub_keys();
        for(auto &key : keys)
        {
            QString combine_key = parent_key + '/' + key;
            res.push_back(combine_key);
            res.append(CombineKey(combine_key, def->sub_property_def(key)));
        }
        return res;
    }
    
}