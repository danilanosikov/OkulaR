#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <ctime>

// raw data
static float vertecies[] =
{
    // x    y
   -0.5f, -0.5f,
    0.0f,  0.5f,
    0.5f, -0.5f
};


void Crash(const char message[]);
void Log(const char message[]);
void Draw(unsigned int gl_shape);
void Clear();
void Move();
unsigned int TweakContext(float (*verticies)[]);
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
    TweakContext(&vertecies); SetLinePreferences();
    
    Loop(window);

    
    
    return 0;
}



void InitializeGLEW(GLFWwindow* window){
    Log("[GLEW Preinitialization]: Searching for Context.");
    if((glfwGetCurrentContext()) == nullptr) {
        Log("[GLEW Preinitialization]:[WARNING]: No context found.");
        Log("[GLEW Preinitialization]: Initializing Context Set-Up...");
        glfwMakeContextCurrent(window);
        if(glfwGetCurrentContext() == nullptr)
        {
            Log("[GLEW Preinitialization]:[ERROR] Context was not created!");
            Crash("[GLEW Preinitialization]:[Context Creation]: FAILURE!");
        }
        else Log("[GLEW Preinstallation]:[Context Creation]: SUCCESS.");
    }
    Log("[GLEW Preinitialization]: Context Found.");
    Log("[GLEW Initialization]: IN PROGRESS...");
    if (GLEW_OK != glewInit()) Crash("[GLEW Initialization]: FAILURE!");
    Log("[GLEW Initialization]: SUCCESS.");
}



void InitializeGLFW(){
    if(!glfwInit()) Crash("[GLFW Initialization]: FAILURE!");
    else Log("[GLFW Initialization]: SUCCESS.");
}




void Draw(unsigned int gl_shape){
    
    glDrawArrays(gl_shape, 0, 3); Log("[Draw]: Shape Drawn to Back Buffer.");
    
    if (gl_shape == GL_POINTS) return;
    else glDrawArrays(GL_POINT, 0, 3); Log("[Draw]: Points Drawn.");
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




unsigned int TweakContext(float (*vertecies)[]){
    
    unsigned int buffer_address;
    // reserve v-ram and returns buffer into buffer variable
    glGenBuffers(1, &buffer_address); Log("[Context Tweaks]: V-RAM Reserved. Address available in buffer_address.");
    // sets the state of this buffer to array buffer - a way to interpert data in it; (assosiate buffer with bufferarray)
    glBindBuffer(GL_ARRAY_BUFFER, buffer_address); Log("[Context Tweaks]: Assosiated buffer, corresponding to buffer_address, with GL_ARRAY_BUFFER.");
    // creates an new data store (just an abstract set of data) for buffer assosiated with arraybuffer Buffer as a verb;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, *vertecies, GL_STATIC_DRAW); Log("[Context Tweaks]: Data Bufferized.");
    // Layout Buffer (locate verticies and its properties in the array) (layouts pointers to specific atributes of any vertex) //(begin, dimentions, type, ??, memory after which next vertex begins, ?? )
    glVertexAttribPointer(0,2, GL_FLOAT, 0, sizeof(float) * 2, 0); Log("[Context Tweaks]: Buffer Layout Complete.");
    
    // Apply attribute settings
    glEnableVertexAttribArray(0); Log("[Context Tweaks]: Changes Applied to the Current Context.");
    
    return buffer_address;
}




GLFWwindow* CreateWindow(const unsigned int height, const unsigned int width, const char[]){
    Log("[Window Creation]: In Progress...");
    GLFWwindow* window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    if(!window) Crash("[Window Creation]: FAILURE!");
    Log("[Window Creation]: SUCCESS.");
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
}



void Update(GLFWwindow* window){ glfwSwapBuffers(window); glfwPollEvents();}





void Crash(const char message[]){
    using namespace std;
    cout << "GLFW Termination...";
    glfwTerminate();
    cout << "--> Terminated." << endl;
    cout << "SOFTWARE EXITED WITH CRITICAL FAILURE: ";
    cout << "-->>| ";
    throw runtime_error(message);
}

void Log(const char message[]){
    using namespace std;
    cout << "[LOG]: ";
    cout << message << endl;
}
