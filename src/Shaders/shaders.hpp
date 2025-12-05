// Copyright 2025 Ajay Alamuri

#pragma once
#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

class Shaders
{
public:
	Shaders(std::string vertexSource, std::string fragmentSource);
	unsigned int GetID() const { return _id; }
private:
	unsigned int _id;
	static char* readShaderFile(const std::string& filename);
};

#endif SHADERS_HPP