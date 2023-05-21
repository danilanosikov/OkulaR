#pragma once

#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Logger.hpp"

namespace OkulaR {

class Window {
    /** A pointer to GLFW Window assosiated with this*/
    GLFWwindow* body;
    /** The size */
    unsigned int width, height;
    /** Name of this*/
    std::string title;
    /** A link to logger, which should work in a saparate thread*/
    Logger* logger;
    
    
    ///@DONE
    /** Initializes GLFW */
    void InitializeGLFW();
    /** Initializes GLEW */
    void InitializeGLEW();
    /** Creates a GLFWwindow */
    void Create();
    
    public:
        /** Runs window rendering continously. */
        void Run();
        /**Constructor **/
        Window(Logger* logger, int width = 800, int height = 640, std::string title = "");
        /**Distructor */
        ~Window();
    };
}
