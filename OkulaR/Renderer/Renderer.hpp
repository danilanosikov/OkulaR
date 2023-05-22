#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GL_SILENCE_DEPRECATION

#include <string>

#include "Logger.hpp"
#include "Shape.hpp"

namespace OkulaR{

struct  Renderer{
	GLFWwindow* window;
    Logger* logger = nullptr;
	
	void InitializeGLFW();
	void InitializeGLEW();
	
    void Run();
	
    void DrawSquare(Shape::Square square);
    void DrawCube(Shape::Cube cube);
    
    void DrawTriangle(Shape::Triangle* triangle);
    
    
    Renderer();
    ~Renderer();
};
}
