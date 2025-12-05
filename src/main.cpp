// Copyright 2025 Ajay Alamuri

#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Input Processing/input.hpp"
#include "Windowing/windowing.hpp"
#include "Shaders/shaders.hpp"
#include "Vertex Array/vertexarray.hpp"

#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)

int main()
{
	// Initialize windowing system and create a window
	GLFWwindow* window = Windowing::InitializeWindowingSystem(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Window");

	// Check if window creation and GLAD initialization were successful
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window or initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Define vertices for a triangle
	float vertices[] {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f,  0.0f, 0.0f,  // Middle Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		0.0f, -0.5f, 0.0f,  // Middle Bottom
	   -0.5f, -0.5f, 0.0f,  // Bottom Left
	   -0.5f,  0.0f, 0.0f,  // Middle Left
	   -0.5f,  0.5f, 0.0f,  // Top Left 
	    0.0f,  0.5f, 0.0f   // Top Middle
	};

	unsigned int indices[] = {  // Note that we start from 0!
		0, 1, 7,  // First Triangle
		1, 2, 3,  // Second Triangle
		3, 4, 5,  // Third Triangle
		5, 6, 7   // Fourth Triangle
	};

	std::string name = "vertexPos";

	VertexArray VAO(name, &vertices[0], sizeof(vertices) / sizeof(vertices[0]), &indices[0], sizeof(indices) / sizeof(indices[0]));

	Shaders programOne("position", "color");

	// Main render loop
	while (!glfwWindowShouldClose(window))
	{
		// Processing done by key callback

		// Render
		glClear(GL_COLOR_BUFFER_BIT);

		// Set the shader program as active
		glUseProgram(programOne.GetID());
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, VAO.GetSize(), GL_UNSIGNED_INT, 0);
		VAO.Unbind();

		// Poll IO events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Clean up and exit
	glfwTerminate();
	return 0;
}