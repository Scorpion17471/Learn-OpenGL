// Copyright 2025 Ajay Alamuri
#include <algorithm>
#include <iostream>

#include "vertexarray.hpp"

VertexArray::VertexArray(std::string vboLabel, float* vertices, int vertexCount, unsigned int* indices, int indexCount)
{
	// Generate and bind a Vertex Array Object (VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and bind a Vertex Buffer Object (VBO) to current GL_ARRAY_BUFFER
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(*vertices)) * vertexCount, vertices, GL_STATIC_DRAW); // Upload vertex data to the current VBO

	GLenum error = glGetError();
	while (error != GL_NO_ERROR) {
		// Handle or log the error
		std::cout << "OpenGL Error: " << error << std::endl;
		error = glGetError();
	}

	// Generate and bind an Element Buffer Object (EBO) to current GL_ELEMENT_ARRAY_BUFFER
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(decltype(*indices)) * indexCount, indices, GL_STATIC_DRAW); // Upload index data to the current EBO

	error = glGetError();
	while (error != GL_NO_ERROR) {
		// Handle or log the error
		std::cout << "OpenGL Error: " << error << std::endl;
		error = glGetError();
	}

	// Define vertex attribute pointers for use and enable
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind to prevent accidental modification
	glBindVertexArray(0);

	std::cout << "Created VAO with ID: " << VAO << ", VBO with ID: " << VBO << ", EBO with ID: " << EBO << std::endl;

	// Store fields
	this->_size = indexCount;
	this->_id = VAO;
	this->_ebo = EBO;
	this->_vbos[vboLabel] = VBO;
}

unsigned int VertexArray::GetVBO(std::string vboLabel) const
{
	std::cout << "Retrieving VBO with label: " << vboLabel << std::endl;

	std::unordered_map<std::string, unsigned int>::const_iterator loc = this->_vbos.find(vboLabel);
	if (loc != this->_vbos.end())
	{
		std::cout << "Retrieved VBO with label: " << vboLabel << " and data: " << loc->second << std::endl;
		return loc->second;
	}
	else
	{
		std::cout << "VBO with label: " << vboLabel << " not found." << std::endl;
		return NULL; // Return 0 if VBO with the given label is not found
	}
}

void VertexArray::Bind() const
{
	std::cout << "Binding VAO with ID: " << this->_id << std::endl;
	glBindVertexArray(this->_id);
}

void VertexArray::Unbind() const
{
	std::cout << "Unbinding VAO with ID: " << this->_id << std::endl;
	glBindVertexArray(0);
}