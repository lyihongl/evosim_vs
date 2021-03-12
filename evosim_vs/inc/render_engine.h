#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H
#include "vertex.h"
#include "shader.h"
namespace EvoSim {
void RenderVertexArray(const VertexArray& dat, const Shader& shader);
};

#endif