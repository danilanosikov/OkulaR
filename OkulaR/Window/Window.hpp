#pragma once

#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Logger.hpp"
#include "Renderer.hpp"

namespace OkulaR {

struct Window {
    /** A pointer to GLFW Window assosiated with this*/
	Renderer renderer = Renderer();
    /** The size */
    unsigned int width, height;
    bool fullscreen;
    /** Name of this*/
    std::string title;
    /** A link to logger, which should work in a saparate thread*/
    Logger* logger;
    
    /** Creates a GLFWwindow */
    void Create();
    
    public:
        /** Runs window rendering continously. */
        void Run();
    
    
        /**Constructor **/
        Window(int width = 800, int height = 640, bool fullscreen = true, std::string title = "", Logger* logger = nullptr);
        /**Distructor */
		~Window();
    };
}
