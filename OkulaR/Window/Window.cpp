#include "Window.hpp"
#include "Renderer.hpp"
#include <string>

namespace OkulaR{

    void Window::InitializeGLFW(){
        if(!glfwInit()) Logger::Crash("Window.InitializeGLFW", "FAILURE! Hint: Check whether GLFW is configured properly in solution properties.", logger);
        else Logger::Record(Log::LOG, "Window.InitializeGLFW", "SUCCESS!", logger);
    }
    void Window::InitializeGLEW(){
        Logger::Record( Log::LOG,"Window.InitializeGLEW", "Searching for Context...", logger);
        
        if((glfwGetCurrentContext()) == nullptr) {
            Logger::Record(Log::WARNING, "Window.InitializeGLEW", "No Context.", logger);
            
            Logger::Record(Log::NOTIFICATION,"Window.InitializeGLEW"," Fixing...", logger);
            glfwMakeContextCurrent(body);
            Logger::Record(Log::NOTIFICATION,"Window.InitializeGLEW"," COMPLETE.", logger);
            
            Logger::Record(Log::NOTIFICATION,"Window.InitializeGLEW"," Researching...", logger);
            if(glfwGetCurrentContext() == nullptr)
            {
                Logger::Record(Log::ERROR, "Window.InitializeGLEW", "No Context Still Found.");
                Logger::Crash("Window.InitializeGLEW", "FAILURE! Hint: Set-Up Context and Make it Current.", logger);
            }
        }
        Logger::Record(Log::LOG, "Window.InitializeGLEW"," Context Found.");
        Logger::Record(Log::LOG, "Window.InitializeGLEW", "Initialization In Progress...");
        if (GLEW_OK != glewInit()) Logger::Crash("Window.InitializeGLEW", "FAILURE! Hint: Check whether GLEW is configured properly in solution properties.", logger);
        Logger::Record(Log::LOG, "Window.InitializeGLEW", "SUCCESS!");
    }
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
            
            body = glfwCreateWindow(mode->width, mode->height, title.c_str(), p_monitor, NULL);
        }
        else body = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        
        if(!body) Logger::Crash("Window.Create", "FAILURE!", logger);
        glfwMakeContextCurrent(body);
        Logger::Record(Log::LOG, "Window.Create", "SUCCESS.", logger);
    }
	void Window::Run(){
    this->logger->WaitToEnd();
	if(draw != 0) {
        draw();
        Logger::Record(Log::LOG, "Window.Run", "Rendering Complete");
    }
    else {
        Logger::Record(Log::WARNING, "Window.Run", "No Draw Implementation Found.", logger);
        while(!glfwWindowShouldClose(body)){
            glClearColor(0.1f, 0.1f, 0.098f, 0.95f);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);
            
            glfwSwapBuffers(body);
            glfwPollEvents();
        }
    }
        this->logger->WaitToEnd();
    }

    Window::Window(int width, int height, bool fullscreen, std::string title, Logger* logger): width(width),height(height),fullscreen(fullscreen), title(title),logger(logger){
		
		
		
		if(!glfwInit()) Logger::Crash("Window.InitializeGLFW", "FAILURE! Hint: Check whether GLFW is configured properly in solution properties.", logger);
		else Logger::Record(Log::LOG, "Window.InitializeGLFW", "SUCCESS!", logger);
        Create();
        InitializeGLEW();
        Run();
    }
    Window::~Window(){
        logger->Record(Log::LOG, "~Window", "Closing Window...!");
        logger->WaitToEnd();
        glfwTerminate();
        if(logger != nullptr && logger->IsActive()) logger->Record(Log::LOG, "~Window", "Window Closed.");
    }
}
