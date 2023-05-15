#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <iostream>
//#include <exception>

int main(){
    
    GLFWwindow* window;
    
    if(!glfwInit()) return -1;
    
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    
    if(!window) { glfwTerminate(); return -1; }
    
    
    // Set-Up Context
    glfwMakeContextCurrent(window);
    
    
    // Initialise GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        return -1;
    }
    
    
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw;
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.0f, 0.5f);
            glVertex2f(0.5f, -0.5f);
        glEnd();
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    }
    
    
    return 0;
}


//int main(void)
//{
//
//    #define GL_SILENCE_DEPRECATION
//
//    // Apple-specific settings
//    #ifdef __APPLE__
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    #endif
//
//
//
//    glfwInit() ?
//        std::cout << "GLFW initialisation SUCCESS\n" :
//        throw std::runtime_error("GLFW initialisation FAILURE\n");
//
//
//    // Init Winodw
//    GLFWwindow* body = glfwCreateWindow(800, 800, "Hello Window", NULL, NULL);
//    body ?
//        std::cout<<"Body creation SUCCESS\n" :
//        throw std::runtime_error("Body creation FAIILURE\n");
//
//    // Apply It's Parameters
//    glfwMakeContextCurrent(body);
//
//    // Main Loop
//    while (!glfwWindowShouldClose(body)){
//
//        // Clearance of colour buffer
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Draw objects
//        glBegin(GL_TRIANGLES);
//            glVertex2f(-0.5f, -0.5f);
//            glVertex2f(0.0f, 0.5f);
//            glVertex2f(0.5f, -0.5f);
//        glEnd();
//        // Swap back buffer and the front one
//        glfwSwapBuffers(body);
//
//
//        glfwPollEvents();
//
//    }
//
//    // Terminate GLFW
//    glfwTerminate();
//
//
//    return 0;
//}
