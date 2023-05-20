#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include "Logger.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <iostream>
#include <ctime>
#include <exception>
#include "Logger.hpp"

Logger::Logger logger_object = Logger::Logger(Logger::Logger::Mode::ALL);
static Logger::Logger* logger = &logger_object;

static float vertecies[] =
{
    // x    y
   -0.5f, -0.5f,
    0.0f,  0.5f,
    0.5f, -0.5f
};
void Draw(unsigned int gl_shape);
void Clear();
void Move();
unsigned int CustomiseContext(float (*verticies)[]);
void SetLinePreferences();
void Initialize();
void InitializeGLEW(GLFWwindow* window);
void InitializeGLFW();
GLFWwindow* CreateWindow(const unsigned int height, const unsigned int width, const char[]);
void Loop(GLFWwindow* window);
void Update(GLFWwindow* window);




int main(){

    InitializeGLFW();

    GLFWwindow* window = CreateWindow(800, 800, "OkulaR"); glfwMakeContextCurrent(window);

    // Initialise GLEW
    InitializeGLEW(window);


    // id of current buffer
    CustomiseContext(&vertecies); SetLinePreferences();

    Loop(window);
    
    logger->WaitToEnd();

    return 0;
}



void InitializeGLEW(GLFWwindow* window){
    logger->CreateLog(Logger::Log::Type::LOG,"GLEW Preinitialization", "Searching for Context...");
    
    if((glfwGetCurrentContext()) == nullptr) {
        logger->CreateLog(Logger::Log::Type::WARNING, "GLEW Preinitialization", "No Context.");
        
        logger->CreateLog(Logger::Log::Type::NOTIFICATION,"GLEW Preinstallation"," Fixing...");
        glfwMakeContextCurrent(window);
        logger->CreateLog(Logger::Log::Type::NOTIFICATION,"GLEW Preinstallation -> Context Selection"," COMPLETE.");
        
        logger->CreateLog(Logger::Log::Type::NOTIFICATION,"GLEW Preinstallation"," Researching...");
        if(glfwGetCurrentContext() == nullptr)
        {
            logger->CreateLog(Logger::Log::Type::ERROR, "GLEW Preinitialization", "No Context.");
            logger->Crash(Logger::Log(Logger::Log::Type::FATAL, "GLEW  Preinitialization", "FAILURE! Hint: Set-Up Context and Make it Current."));
        }
    }
    logger->CreateLog(Logger::Log::Type::LOG, "GLEW Preinitialization"," Context Found.");
    logger->CreateLog(Logger::Log::Type::LOG, "GLEW Initialization", "IN PROGRESS...");
    if (GLEW_OK != glewInit()) logger->Crash(Logger::Log(Logger::Log::Type::FATAL, "GLEW Initialization", "FAILURE! Hint: Check whether GLEW is configured properly in solution properties."));
    logger->CreateLog(Logger::Log::Type::LOG, "GLEW Initialization", "SUCCESS.");
}



void InitializeGLFW(){
    if(!glfwInit()) logger->Crash(Logger::Log(Logger::Log::Type::FATAL, "GLFW Initialization", "FAILURE! Hint: Check whether GLEW is configured properly in solution properties."));
    else logger->CreateLog(Logger::Log::Type::LOG, "GLFW Initialization", "SUCCESS.");
}




void Draw(unsigned int gl_shape){
    glDrawArrays(gl_shape, 0, 3);
    if (gl_shape == GL_POINTS) return;
    else glDrawArrays(GL_POINT, 0, 3);
}
void Clear(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_VERTEX_ARRAY);
}
void Move(){
    glPushMatrix();
    glRotatef(1.0f, 50.1f, 80.5f, 10.1f);
}




unsigned int CustomiseContext(float (*vertecies)[]){

    unsigned int buffer_address;
    // reserve v-ram and returns buffer into buffer variable
    glGenBuffers(1, &buffer_address); logger->CreateLog(Logger::Log::Type::LOG, "Context Customisation", "V-RAM Reserved. Address available in buffer_address.");
    // sets the state of this buffer to array buffer - a way to interpert data in it; (assosiate buffer with bufferarray)
    glBindBuffer(GL_ARRAY_BUFFER, buffer_address); logger->CreateLog(Logger::Log::Type::LOG, "Context Customisation", "Assosiated buffer, corresponding to buffer_address, with GL_ARRAY_BUFFER.");
    // creates an new data store (just an abstract set of data) for buffer assosiated with arraybuffer Buffer as a verb;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, *vertecies, GL_STATIC_DRAW); logger->CreateLog(Logger::Log::Type::LOG, "Context Customisation", "Data Bufferized.");
    // Layout Buffer (locate verticies and its properties in the array) (layouts pointers to specific atributes of any vertex) //(begin, dimentions, type, ??, memory after which next vertex begins, ?? )
    glVertexAttribPointer(0,2, GL_FLOAT, 0, sizeof(float) * 2, 0); logger->CreateLog(Logger::Log::Type::LOG, "Context Customisation", "Buffer Layout Complete.");

    // Apply attribute settings
    glEnableVertexAttribArray(0); logger->CreateLog(Logger::Log::Type::LOG, "Context Customisation", "Changes Applied to the Current Context.");

    return buffer_address;
}




GLFWwindow* CreateWindow(const unsigned int height, const unsigned int width, const char[]){
    logger->CreateLog(Logger::Log::Type::LOG, "Window Creation", "In Progress...");
    GLFWwindow* window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    if(!window) logger->Crash(Logger::Log(Logger::Log::Type::FATAL, "Window Creation", "FAILURE!"));
    logger->CreateLog(Logger::Log::Type::LOG, "Window Creation", "SUCCESS.");
    return window;
}




void SetLinePreferences(){
    glLineWidth(20);
    glPointSize(30);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_LINE_SMOOTH);
}



void Loop(GLFWwindow* window){
    while(!glfwWindowShouldClose(window)){
        Clear(); (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) ? Draw(GL_LINE_LOOP) : Draw(GL_POINTS);
        Move();
        Update(window);
    }
    logger->WaitToEnd();
}



void Update(GLFWwindow* window){ glfwSwapBuffers(window); glfwPollEvents();}
