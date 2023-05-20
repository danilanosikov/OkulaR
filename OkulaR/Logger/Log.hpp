#pragma once

#include <string>
#include <iostream>
#include <queue>


namespace Logger{


class Log{
    const std::string body;
public:
    enum Type{
        NOTIFICATION = 0,
        SUGGUESTION = 1,
        LOG = 2,
        WARNING = 3,
        ERROR = 4,
        FATAL = 5,
    };
    std::string message;
    const Type type;
    const std::string occurance;
    
    Log(Type type, std::string occurance, std::string body);
    ~Log();
    std::string ToString();
    void Print();
    
private:
    void Compose();
    std::string Format(std::string text);
    std::string ToString(Type type);
};
}
