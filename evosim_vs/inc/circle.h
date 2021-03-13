#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <optional>

#include "vertex.h"


namespace EvoSim {
	struct Circle {
		static const std::vector<std::size_t> AttribPoints;
		static const std::vector<std::size_t> EboPoints;
		glm::vec2 Position;
		glm::vec3 Color;
		//void AddtoVa(VertexArray& va, std::optional<std::size_t> index = std::nullopt);
		Circle(glm::vec2 position = { 0, 0 }, glm::vec3 color = { 0, 0, 0 });
	};
}
