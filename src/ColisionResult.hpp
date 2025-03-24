#pragma once

#include <string>

class ColisionResult
{
public:
    enum Type
    {
        NONE,
        EXIT,
        TELEPORT
    };
private:
    Type type = NONE;
    std::string target;

public:
    ColisionResult() = default;
    ColisionResult(std::string s, Type t) {
        type = t;
        target = s;
    }
    Type getType() const {
        return type;
    }
    const std::string& getTarget() const {
        return target;
    }
};

