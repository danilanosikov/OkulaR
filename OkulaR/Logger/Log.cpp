#include "Log.hpp"
#include <thread>
#include <queue>

using namespace Logger;


    
    Log::Log(Type type, std::string occurance, std::string body): type(type), body(body), occurance(occurance)
    {
        Compose();
    }
    Log::~Log(){}

    /* Composes and Formats final message */
    void Log::Compose()
    {
        std::string var;
        if(occurance != "") var = "[IN:/" + occurance + "]:";
        else var = occurance;
        message = ToString(type) + var + " " + body;
    }

    std::string Log::Format(std::string text){
        return "[" + text + "]:";
    }

    /* Converts Log to String */
    std::string Log::ToString() { return message; }
    /* Converts Log Type to String */
    std::string Log::ToString(Type type)
    {
        
        std::string var;
        switch(type){
            case NOTIFICATION:
                var = "NOTIFICATION";
                break;
            case SUGGUESTION:
                var = "SUGGUESTION";
                break;
            case LOG:
                var = "LOG";
                break;
            case WARNING:
                var = "WARNING";
                break;
            case ERROR:
                var = "ERROR";
                break;
            case FATAL:
                var = "FATAL";
                break;
        }
        return Format(var);
}

void Log::Print(){
    std::cout<< ToString() << std::endl;
}


