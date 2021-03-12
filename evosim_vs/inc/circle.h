#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "vertex.h"


namespace EvoSim {
	static const std::vector<std::size_t> AttribPoints{ 0, 2, 5 };
	struct Circle {
		glm::vec2 Position;
		glm::vec2 Color;
		void AddtoVa(VertexArray& va);
	};
}
