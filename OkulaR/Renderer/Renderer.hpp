#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GL_SILENCE_DEPRECATION

#include <string>

#include "Logger.hpp"
#include "Window.hpp"

namespace OkulaR{

struct  Renderer{
	Window window;
    Logger* logger = nullptr;
	
	void CreateWindow(int width, int haight, bool fullscreen, std::string title);
	
    void Draw();
    void DrawTest();
    void DrawSquare(GLfloat OX, GLfloat OY, GLfloat OZ, GLfloat size);
    void DrawCube(GLfloat centreX, GLfloat centreY, GLfloat centreZ, GLfloat edgelength);
    
    void DrawTriangle();
    void DrawCircle();
    
    
    Renderer(GLFWwindow* window);
    ~Renderer();
};
}
