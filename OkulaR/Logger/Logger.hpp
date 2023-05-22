#pragma once
#include <queue>
#include "Log.hpp"
#include <thread>

namespace OkulaR{

    class Logger{
        public:
            enum Mode{
                NONE = 0,
                FATAL = 1,
                ERROR = 2,
                WARNING = 3,
                LOG = 4,
                ALL = 5,
                NOTIFICATION = 6,
                SUGGUESTION = 7
            };
        private:
            Mode mode;
            std::queue<Log> buffer;
            // Checks whether Log type correspond to correct mode;
            bool Approve(Log* log);
            // Executes Logger Once
            void Execute();
            void Run();
        public:
            std::thread _thread;
            // Stashes Log to logging queue;
            static void Record(Log::Type type = Log::LOG, std::string occurance = "", std::string message = "Log Message Empty.", Logger* logger = nullptr);
            // Releases all logs in queue;
            void Flush();
            // Sets Logging Mode;
            void Set(Mode mode);
            std::queue<Log> GetBuffer();
            static void WaitToEnd(Logger* logger = nullptr);
            // Checks whether logger is logging
            bool IsActive();
        
            void Sync();
            void Async();
        
            static void Crash(std::string where = "", std::string error_message = "FAILURE!", Logger* logger = nullptr);
        
            Logger(Mode mode);
           ~Logger();
    };
}
