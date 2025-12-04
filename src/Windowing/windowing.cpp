// Copyright 2025 Ajay Alamuri

#include "../Input Processing/input.hpp"
#include "windowing.hpp"

GLFWwindow* Windowing::initializeWindowingSystem(int width, int height, std::string title)
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a Window with OpenGL Context
	GLFWwindow* window = glfwCreateWindow(
		width,
		height,
		"OpenGL Window",
		NULL,
		NULL
	);

	// Check if the window was created successfully and if GLAD was loaded
	if (window == NULL)
	{
		return NULL;
	}

	// Bind the OpenGL context to the window
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return NULL;
	}

	// Set viewport (binds the OpenGL rendering area to the window size)
	glViewport(0, 0, width, height);

	// Set the framebuffer size callback to adjust viewport on window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set key callback for input processing
	glfwSetKeyCallback(window, Inputs::processInput);

	return window;
}

void Windowing::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}