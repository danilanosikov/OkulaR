#include "Logger.hpp"
#include "Window.hpp"

using namespace OkulaR;

int main(){
    Logger logger(Logger::Mode::NONE);
    Window okular_main(&logger);
    return 0;
}

