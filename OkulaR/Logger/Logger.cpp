#include "Logger.hpp"

#include <thread>
#include <chrono>

namespace OkulaR{

    void Logger::CreateLog(Log::Type type, std::string occurance, std::string message){
        if(!IsActive()) return;
        Log temp_log = Log(type, occurance, message);
        if(!Approve(&temp_log)) return;
        buffer.push(temp_log);
    }
    void Logger::CreateLog(Log::Type type, std::string message){
        CreateLog(type, "", message);
    }


    void Logger::Run(){
        if(!IsActive()) return;
        _thread = std::thread(
            [this]() {
                while(IsActive())Execute();
            }
        );
        Async();
    }

    void Logger::Execute(){
        if(buffer.empty()) return;
        Flush();
    }
    void Logger::Flush() {
        while(!buffer.empty()){ buffer.front().Print(); buffer.pop();}
    }
    bool Logger::Approve(Log* log){
        switch(mode){
            case NONE:
                return false;
                break;
            case ALL:
                return true;
                break;
            case FATAL:
                if(log->type == Log::FATAL) return true;
                else return false;
                break;
            case ERROR:
                if(log->type == Log::ERROR) return true;
                else return false;
                break;
            case WARNING:
                if(log->type == Log::WARNING) return true;
                else return false;
                break;
            case LOG:
                if(log->type == Log::LOG) return true;
                else return false;
                break;
            case NOTIFICATION:
                if(log->type == Log::NOTIFICATION) return true;
                else return false;
                break;
            case SUGGUESTION:
                if(log->type == Log::SUGGUESTION) return true;
                else return false;
                break;
        }
    }
    void Logger::Set(Mode mode){
        Sync();
        
        this->mode = mode;
        CreateLog(Log::Type::LOG, "Logger Runtime", "Logger Mode Has been Changed");
        
        Async();
        
    }
    void Logger::WaitToEnd(){
        if(!buffer.empty()) std::this_thread::sleep_for(std::chrono::milliseconds(buffer.size()));
    }
    std::queue<Log> Logger::GetBuffer(){
        return buffer;
    }
    bool Logger::IsActive(){
        switch(mode){
            case NONE:
                return false;
                break;
            default:
                return true;
                break;
        }
    }
    
    void Logger::Sync(){
        if(_thread.joinable())_thread.join();
    }
    void Logger::Async(){
        if(_thread.joinable())_thread.detach();
    }

    void Logger::Crash(Log log){
        CreateLog(log.type, log.occurance,log.message);
        WaitToEnd();
        throw std::runtime_error("Application Crashed!");
    }

    Logger::Logger(Mode mode) : mode(mode) {
        CreateLog(Log::Type::LOG, "Logger Initialization", "IN PROGRESS...");
        Run();
        CreateLog(Log::Type::LOG, "Logger Initialization", "DONE.");
    }
    Logger::~Logger(){
        CreateLog(Log::Type::LOG, "Logger Distruction", "Shutting Down Logger...");
        WaitToEnd();
        Sync();
        if(IsActive()) std::cout << "Shutdown Complete. Logger will be no more\n";
    }
}
