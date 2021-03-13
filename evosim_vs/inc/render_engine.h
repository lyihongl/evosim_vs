#pragma once
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include "vertex.h"
#include "shader.h"
namespace EvoSim {
	/*
	
void RenderStaticVertexArray(const VertexArray& dat, const Shader& shader);
void RenderDynamicVertexArray(const VertexArray& dat, const Shader& shader);
	
	*/
struct VertexManager {
	enum BufferType{Vertex, Element};
	VertexManager();
	std::unordered_map<std::string, GLuint> VertexArrayObjects;
	std::unordered_map<std::string, GLuint> VertexArrayBuffers;
	std::unordered_map<std::string, GLuint> VertexElementBuffers;
	std::size_t DynamicBufferFill;
	void CreateArrayObj(GLuint& id);
	void CreateBufferObj(GLuint& id);
	void CreateArrayObj(std::string name);
	void CreateBufferObj(std::string name, BufferType type);
};
};
