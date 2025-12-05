// Copyright 2025 Ajay Alamuri

#pragma once
#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>
#include <vector>

class VertexArray
{
public:
	VertexArray(std::string vboLabel, float* vertices, int vertexCount, unsigned int* indices, int indexCount);
	unsigned int GetID() const { return this->_id; }
	unsigned int GetEBO() const { return this->_ebo; }
	unsigned int GetVBO(std::string vboLabel) const;
	int GetSize() const { return this->_size; };
	void Bind() const;
	void Unbind() const;
private:
	int _size;
	unsigned int _id;
	unsigned int _ebo;
	std::unordered_map<std::string, unsigned int> _vbos;
};

#endif VERTEXARRAY_HPP