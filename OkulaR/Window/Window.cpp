#include "Window.hpp"
#include <string>

namespace OkulaR{

    void Window::InitializeGLFW(){
        if(!glfwInit()) logger->Crash(Log(Log::Type::FATAL, "GLFW Initialization", "FAILURE! Hint: Check whether GLEW is configured properly in solution properties."));
        else logger->CreateLog(Log::Type::LOG, "GLFW Initialization", "SUCCESS.");
    }
    void Window::InitializeGLEW(){
        logger->CreateLog(Log::Type::LOG,"GLEW Preinitialization", "Searching for Context...");
        
        if((glfwGetCurrentContext()) == nullptr) {
            logger->CreateLog(Log::Type::WARNING, "GLEW Preinitialization", "No Context.");
            
            logger->CreateLog(Log::Type::NOTIFICATION,"GLEW Preinstallation"," Fixing...");
            glfwMakeContextCurrent(body);
            logger->CreateLog(Log::Type::NOTIFICATION,"GLEW Preinstallation -> Context Selection"," COMPLETE.");
            
            logger->CreateLog(Log::Type::NOTIFICATION,"GLEW Preinstallation"," Researching...");
            if(glfwGetCurrentContext() == nullptr)
            {
                logger->CreateLog(Log::Type::ERROR, "GLEW Preinitialization", "No Context.");
                logger->Crash(Log(Log::Type::FATAL, "GLEW  Preinitialization", "FAILURE! Hint: Set-Up Context and Make it Current."));
            }
        }
        logger->CreateLog(Log::Type::LOG, "GLEW Preinitialization"," Context Found.");
        logger->CreateLog(Log::Type::LOG, "GLEW Initialization", "IN PROGRESS...");
        if (GLEW_OK != glewInit()) logger->Crash(Log(Log::Type::FATAL, "GLEW Initialization", "FAILURE! Hint: Check whether GLEW is configured properly in solution properties."));
        logger->CreateLog(Log::Type::LOG, "GLEW Initialization", "SUCCESS.");
    }
    void Window::Create(){
        logger->CreateLog(Log::Type::LOG, "Window Creation", "In Progress...");
        body = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if(!body) logger->Crash(Log(Log::Type::FATAL, "Window Creation", "FAILURE!"));
        logger->CreateLog(Log::Type::LOG, "Window Creation", "SUCCESS.");
    }


    void Window::Run(){
        logger->WaitToEnd();
        
        float verticies[6] = {
            0.1, 0.85,
            -0.3, -0.2,
            -0.5, 0.9
        };

        unsigned int buffer_address;
        // reserve v-ram and returns buffer into buffer variable
        glGenBuffers(1, &buffer_address); logger->CreateLog(Log::Type::LOG, "Context Customisation", "V-RAM Reserved. Address available in buffer_address.");
        // sets the state of this buffer to array buffer - a way to interpert data in it; (assosiate buffer with bufferarray)
        glBindBuffer(GL_ARRAY_BUFFER, buffer_address); logger->CreateLog(Log::Type::LOG, "Context Customisation", "Assosiated buffer, corresponding to buffer_address, with GL_ARRAY_BUFFER.");
        // creates an new data store (just an abstract set of data) for buffer assosiated with arraybuffer Buffer as a verb;
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &verticies, GL_STATIC_DRAW); logger->CreateLog(Log::Type::LOG, "Context Customisation", "Data Bufferized.");
        // Layout Buffer (locate verticies and its properties in the array) (layouts pointers to specific atributes of any vertex) //(begin, dimentions, type, ??, memory after which next vertex begins, ?? )
        glVertexAttribPointer(0,2, GL_FLOAT, 0, sizeof(float) * 2, 0); logger->CreateLog(Log::Type::LOG, "Context Customisation", "Buffer Layout Complete.");
        // Apply attribute settings
        glEnableVertexAttribArray(0); logger->CreateLog(Log::Type::LOG, "Context Customisation", "Changes Applied to the Current Context.");

        // Line Preferences
        glLineWidth(20);
        glPointSize(30);
        glEnable(GL_LINE_STIPPLE);
        glEnable(GL_LINE_SMOOTH);
        
        while (!glfwWindowShouldClose(body)){
            // Clear
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_VERTEX_ARRAY);
            
            // Actual Draw
            (glfwGetKey(body, GLFW_KEY_E) == GLFW_PRESS) ? glDrawArrays(GL_LINE_LOOP, 0, 3) : glDrawArrays(GL_POINTS, 0, 3);
            glPushMatrix();
            glRotatef(1.0f, 50.1f, 80.5f, 10.1f);
        
            // Refresh Window
            glfwSwapBuffers(body);
            glfwPollEvents();
        }
        this->logger->WaitToEnd();
    }

    Window::Window(Logger* logger, int width, int height, std::string title): logger(logger),width(width),height(height),title(title) {
        InitializeGLFW();
        Create();
        InitializeGLEW();
        Run();
    }
    Window::~Window(){
        logger->CreateLog(Log::Type::LOG,"Bye!");
        logger->WaitToEnd();
        glfwSetWindowShouldClose(body, GLFW_TRUE);
        glfwTerminate();
    }
}
