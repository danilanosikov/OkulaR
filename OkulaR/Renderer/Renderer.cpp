#include "Renderer.hpp"



namespace OkulaR{
	
	
	void Renderer::InitializeGLFW(){
		if(!glfwInit()) Logger::Crash("Window.InitializeGLFW", "FAILURE! Hint: Check whether GLFW is configured properly in solution properties.", logger);
		else Logger::Record(Log::LOG, "Window.InitializeGLFW", "SUCCESS!", logger);
	}
	void Renderer::InitializeGLEW(){
		Logger::Record( Log::LOG,"Window.InitializeGLEW", "Searching for Context...", logger);
		
		if((glfwGetCurrentContext()) == nullptr) {
			Logger::Record(Log::WARNING, "Window.InitializeGLEW", "No Context.", logger);
			
			Logger::Record(Log::NOTIFICATION,"Window.InitializeGLEW"," Fixing...", logger);
			glfwMakeContextCurrent(window);
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
	
	void Renderer::Run(){
		auto gl_window = this->window;
		
		
//		Shape::Point p1(-1.0f, -1.0f, 0.0f);
//		Shape::Point p2(0.0f, 1.0f, 0.0f);
//		Shape::Point p3(1.0f, -1.0f, 0.0f);
//		Shape::Triangle triangle(p1, p2, p3);
		
		
		
		while(!glfwWindowShouldClose(gl_window)){
			// Clear
			glClearColor(0.1f, 0.1f, 0.098f, 0.95f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);
			
			
			
			
			//this->DrawTriangle(&triangle);
			this->DrawSquare(Shape::Point(0.0f, 0.0f, 0.0f), 0.5);
			
			
			glPushMatrix();
			//glRotatef(1, 0, 0, 1);
			

			glfwSwapBuffers(gl_window);
			glfwPollEvents();
			
			// Update
		}
		this->logger->WaitToEnd();
	}

	void Renderer::DrawTriangle(Shape::Triangle* triangle){
		
		float vertex_array[] = {
			triangle->points[0].position[0], triangle->points[0].position[1], triangle->points[0].position[2],
			triangle->points[1].position[0], triangle->points[1].position[1], triangle->points[1].position[2],
			triangle->points[2].position[0], triangle->points[2].position[1], triangle->points[2].position[2],
		};
		
		GLuint buffer_id;
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array), vertex_array , GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	void Renderer::DrawSquare(Shape::Point centre, float side){
		
		float shift = side/2;
		
		float ox = centre.position[0];
		float oy = centre.position[1];
		float oz = centre.position[2];
		
		Shape::Point p1(ox - shift, oy - shift, oz);
		Shape::Point p2(ox + shift, oy + shift, oz);
		Shape::Point p3(ox + shift, oy - shift, oz);
		Shape::Point p4(ox - shift, oy + shift, oz);
		
		Shape::Triangle trig1(p1, p2, p3);
		Shape::Triangle trig2(p1, p4, p2);
		
		DrawTriangle(&trig1);
		DrawTriangle(&trig2);
	}
	
	Renderer::Renderer(){
		
	}
	Renderer::~Renderer(){
		glfwTerminate();
	}
}
