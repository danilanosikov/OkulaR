#pragma once
#include <queue>
#include "Log.hpp"
#include <thread>

namespace Logger{

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
            void CreateLog(Log::Type type, std::string occurance, std::string message);
            // Same, but no occurance location;
            void CreateLog(Log::Type type, std::string message);
            // Releases all logs in queue;
            void Flush();
            // Sets Logging Mode;
            void Set(Mode mode);
            std::queue<Log> GetBuffer();
            void WaitToEnd();
            // Checks whether logger is logging
            bool IsActive();
        
            void Sync();
            void Async();
        
            void Crash(Log log);
        
            Logger(Mode mode);
           ~Logger();
    };
}
