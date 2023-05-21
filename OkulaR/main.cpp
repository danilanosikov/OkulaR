#include "Logger.hpp"
#include "Window.hpp"

using namespace OkulaR;

Logger logger_object = Logger(Logger::Mode::ALL);
static Logger* logger = &logger_object;

int main(){
    
    Window okular_main(logger);

    return 0;
}

