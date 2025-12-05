// Copyright 2025 Ajay Alamuri
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>

#include "shaders.hpp"

char* Shaders::readShaderFile(const std::string& filename)
{
	// Open file at the end to get the size easily, read binary mode to avoid newline translations
	std::ifstream file("resource/" + filename, std::ios::ate | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filename << std::endl;
		return nullptr;
	}

	// Get file size and allocate buffer
	size_t fileSize = file.tellg();
	char* buffer = new char[fileSize + 1];

	// Read file contents into buffer + null terminator
	file.seekg(0);
	file.read(buffer, fileSize);
	buffer[fileSize] = '\0';

	// Close file and return buffer
	file.close();
	return buffer;
}

Shaders::Shaders(std::string vertexSource, std::string fragmentSource)
{
	/*
	*		VERTEX SHADER
	*/

	// Get filename using name, shader extension, and .glsl extension for consistent formatting

	const char* vertexCode = readShaderFile(vertexSource + ".vert.glsl");

	// Fail if file not read successfully
	if (vertexCode == nullptr)
	{
		return;
	}
	
	// Create Vertex Shader Object, load source code, and compile
	unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexCode, NULL);
	glCompileShader(vertexID);

	// Check for Vertex Shader compilation errors
	int success;
	char shaderLog[512];
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success); // Gets shader compilation status
	if (!success)
	{
		glGetShaderInfoLog(vertexID, 512, NULL, shaderLog); // Gets shader compilation error log
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << shaderLog << std::endl;
	}

	delete[] vertexCode;
	vertexCode = nullptr;

	/*
	*		FRAGMENT SHADER
	*/

	// Get filename using name, shader extension, and .glsl extension for consistent formatting

	const char* fragmentCode = readShaderFile(fragmentSource + ".frag.glsl");

	// Fail if file not read successfully
	if (fragmentCode == nullptr)
	{
		return;
	}

	//// Generate Fragment Shader ID Space
	unsigned int fragmentID;
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER); // Create Fragment Shader Object
	glShaderSource(fragmentID, 1, &fragmentCode, NULL);
	glCompileShader(fragmentID);

	//// Check for Fragment Shader compilation errors
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success); // Gets shader compilation status
	if (!success)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, shaderLog); // Gets shader compilation error log
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << shaderLog << std::endl;
	}

	delete[] fragmentCode;
	fragmentCode = nullptr;

	/*
	*		SHADER PROGRAM LINKING
	*/

	// Create Shader Program and link shaders
	unsigned int ID;
	ID = glCreateProgram(); // Create and Bind Shader Program Object
	glAttachShader(ID, vertexID); // Attach Vertex Shader to Shader Program
	glAttachShader(ID, fragmentID); // Attach Fragment Shader to Shader Program
	glLinkProgram(ID); // Link Shader Program

	// Check for Shader Program linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success); // Gets shader program linking status
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, shaderLog); // Gets shader program linking error log
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << shaderLog << std::endl;
	}

	this->_id = ID;

	// Delete shader objects after linking
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}