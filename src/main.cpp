// Copyright 2025 Ajay Alamuri

#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input Processing/input.hpp"
#include "Windowing/windowing.hpp"
#include "Shaders/shaders.hpp"

#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)

int main()
{
	// Initialize windowing system and create a window
	GLFWwindow* window = Windowing::initializeWindowingSystem(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Window");

	// Check if window creation and GLAD initialization were successful
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window or initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// VAO Sandboxing -- BEGIN

	// Define vertices for a triangle
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
	   -0.5f, -0.5f, 0.0f,  // Bottom Left
	   -0.5f,  0.5f, 0.0f   // Top Left 
	};

	unsigned int indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	// Generate and bind a Vertex Array Object (VAO) -- Container for VBO, attributes (shaders n such), and EBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and bind a Vertex Buffer Object (VBO) to current GL_ARRAY_BUFFER
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Upload vertex data to the current VBO

	// Generate and bind an Element Buffer Object (EBO) to current GL_ELEMENT_ARRAY_BUFFER
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Upload index data to the current EBO

	// Define vertex attribute pointers for use and enable
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// VAO Sandboxing -- END

	// Shader Sandboxing -- BEGIN

	// Vertex Shader Source Code
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// Generate Vertex Shader ID Space
	unsigned int vertexShader;

	// Create Vertex Shader Object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach Vertex Shader Source Code to Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// Compile Vertex Shader
	glCompileShader(vertexShader);

	// Check for Vertex Shader compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // Gets shader compilation status
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // Gets shader compilation error log
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader Source Code
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	// Generate Fragment Shader ID Space
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for Fragment Shader compilation errors
	char fragmentLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // Gets shader compilation status
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentLog); // Gets shader compilation error log
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentLog << std::endl;
	}

	// Create Shader Program and link shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); // Create and Bind Shader Program Object
	glAttachShader(shaderProgram, vertexShader); // Attach Vertex Shader to Shader Program
	glAttachShader(shaderProgram, fragmentShader); // Attach Fragment Shader to Shader Program
	glLinkProgram(shaderProgram); // Link Shader Program

	// Check for Shader Program linking errors
	char programLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // Gets shader program linking status
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, programLog); // Gets shader program linking error log
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << programLog << std::endl;
	}

	// Delete shader objects after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Shader Sandboxing -- END

	// Main render loop
	while (!glfwWindowShouldClose(window))
	{
		// Processing done by key callback

		// Render
		glClear(GL_COLOR_BUFFER_BIT);

		// Set the shader program as active
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Poll IO events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Clean up and exit
	glfwTerminate();
	return 0;
}