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
		glMatrixMode(GL_MODELVIEW);
		
		while(!glfwWindowShouldClose(gl_window)){
			// Clear
			glClearColor(0.1f, 0.1f, 0.098f, 0.95f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);

			this->DrawCube(Shape::Cube(Shape::Point(0,0,0), 0.5));
			glRotatef(1, 0, 1, 0);

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
	void Renderer::DrawSquare(Shape::Square square){
		DrawTriangle(&square.triangle1);
		DrawTriangle(&square.triangle2);
	}
	void Renderer::DrawCube(Shape::Cube cube){
		glPushMatrix();
		glRotated(20, 1, 0, 0);
		DrawSquare(Shape::Square(cube.front_face, cube.side));
		DrawSquare(Shape::Square(cube.back_face, cube.side));
		
		glRotated(90, 0, 1, 0);
		DrawSquare(Shape::Square(cube.front_face, cube.side));
		DrawSquare(Shape::Square(cube.back_face, cube.side));
		
		glRotated(90, 1, 0, 0);
		DrawSquare(Shape::Square(cube.front_face, cube.side));
		DrawSquare(Shape::Square(cube.back_face, cube.side));
		
		glPopMatrix();
		
	}
	
	
	
	Renderer::Renderer(){
		
	}
	Renderer::~Renderer(){
		glfwTerminate();
	}
}
