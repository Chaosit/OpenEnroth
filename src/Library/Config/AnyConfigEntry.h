#pragma once

#include <string>
#include <functional>
#include <any>

#include "ConfigFwd.h"

class AnyConfigEntry {
 public:
    using Validator = std::function<std::any(std::any)>;

    AnyConfigEntry(ConfigSection *section, const std::string &name, std::any defaultValue, Validator validator,
                   AnySerializer *serializer, const std::string &description);
    virtual ~AnyConfigEntry() = default;

    const std::type_info &type() const {
        return _defaultValue.type();
    }

    const std::any &defaultValue() const {
        return _defaultValue;
    }

    const std::any &value() const {
        return _value;
    }

    void setValue(std::any value);

    void reset() {
        _value = _defaultValue;
    }

    std::string defaultString() const;

    std::string string() const;

    void setString(const std::string &value);

    ConfigSection *section() const {
        return _section;
    }

    const std::string &name() const {
        return _name;
    }

    const std::string &description() const {
        return _description;
    }

 protected:
    Validator validator() const {
        return _validator;
    }

 private:
    ConfigSection *_section = nullptr;
    std::string _name;
    std::string _description;
    Validator _validator = nullptr;
    AnySerializer *_serializer = nullptr;
    std::any _value;
    std::any _defaultValue;
};