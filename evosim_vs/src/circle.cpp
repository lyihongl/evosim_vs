#include "../inc/circle.h"

/*
void EvoSim::Circle::AddtoVa
(
	VertexArray& va,
	std::optional<std::size_t> index) {

	va.PushVertexRow({ 0.1f + this->Position[0], -0.1f + this->Position[1], 1.0f, 0, 0, this->Position[0], this->Position[1] });
	va.PushVertexRow({ -0.1f + this->Position[0], -0.1f + this->Position[1], 1.0f, 0.5f, 0, this->Position[0], this->Position[1] });
	va.PushVertexRow({ -0.1f + this->Position[0], 0.1f + this->Position[1], 1.0f, 0, 0, this->Position[0], this->Position[1] });
	va.PushVertexRow({ 0.1f + this->Position[0], 0.1f + this->Position[1], 1.0f, 0, 1.0f, this->Position[0], this->Position[1] });

	va.BufferDynamicData(index);
}
*/

EvoSim::Circle::Circle(glm::vec2 position, glm::vec3 color) {
}

const std::vector<std::size_t> EvoSim::Circle::AttribPoints = { 0, 2, 5 };
const std::vector<std::size_t> EvoSim::Circle::EboPoints = { 0,1,2,2,3,0 };
