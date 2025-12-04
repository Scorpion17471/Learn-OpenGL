// Copyright 2025 Ajay Alamuri

#include "input.hpp"

// Function to process input
void Inputs::processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Process key inputs
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) Escape(window);
	if (key == GLFW_KEY_R && action == GLFW_PRESS) RKey(window);
	if (key == GLFW_KEY_G && action == GLFW_PRESS) GKey(window);
	if (key == GLFW_KEY_B && action == GLFW_PRESS) BKey(window);
	if (key == GLFW_KEY_W && action == GLFW_PRESS) WKey(window);
}

// Escape key processing (Close)
void Inputs::Escape(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, true);
}

// R key processing (Red)
void Inputs::RKey(GLFWwindow* window)
{
	// Set clear color state to red
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

// G key processing (Green)
void Inputs::GKey(GLFWwindow* window)
{
	// Set clear color state to green
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

// B key processing	(Blue)
void Inputs::BKey(GLFWwindow* window)
{
	// Set clear color state to blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// W key processing	(Wireframe)
void Inputs::WKey(GLFWwindow* window)
{
	// Get current polygon mode
	GLint mode[2];
	glGetIntegerv(GL_POLYGON_MODE, mode); // mode[0] = front, mode[1] = back

	if (mode[0] != GL_FILL && mode[1] != GL_FILL)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	return;
}