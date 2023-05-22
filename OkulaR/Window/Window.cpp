#include "Window.hpp"
#include "Renderer.hpp"
#include <string>

namespace OkulaR{

    void Window::Create(){
        Logger::Record(Log::LOG, "Window.Create", "Creation In Progress...");
        auto p_monitor = glfwGetPrimaryMonitor();
        
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        
        if(fullscreen == true){
            const GLFWvidmode* mode = glfwGetVideoMode(p_monitor);
            
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            
            renderer.window = glfwCreateWindow(mode->width, mode->height, title.c_str(), p_monitor, NULL);
        }
        else renderer.window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        
        if(!renderer.window) Logger::Crash("Window.Create", "FAILURE!", logger);
        glfwMakeContextCurrent(renderer.window);
        Logger::Record(Log::LOG, "Window.Create", "SUCCESS.", logger);
    }
	
	void Window::Run(){
    this->logger->WaitToEnd();
		renderer.Run();
        Logger::Record(Log::LOG, "Window.Run", "Rendering Complete");
        this->logger->WaitToEnd();
    }

    Window::Window(int width, int height, bool fullscreen, std::string title, Logger* logger): width(width),height(height),fullscreen(fullscreen), title(title),logger(logger){
        renderer.InitializeGLFW();
        Create();
        renderer.InitializeGLEW();
        Run();
    }
	
    Window::~Window(){
        logger->Record(Log::LOG, "~Window", "Closing Window...!");
        logger->WaitToEnd();
		renderer.~Renderer();
		logger->WaitToEnd();
        if(logger != nullptr && logger->IsActive()) logger->Record(Log::LOG, "~Window", "Window Closed.");
    }
}
