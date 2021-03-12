#include "../inc/vertex.h"
EvoSim::VertexArray::VertexArray(const std::size_t &cols,
								 std::vector<std::size_t> &&attribPoints)
	: cols{cols} {
	this->attribPoints = attribPoints;
	std::cout << attribPoints.size() << std::endl;
	glGenVertexArrays(1, &StaticVAO);
	glGenBuffers(1, &StaticVBO);
	glGenBuffers(1, &StaticEBO);
}
const std::size_t EvoSim::VertexArray::GetRows() {
	return Vertices.size() / cols;
}
void EvoSim::VertexArray::PushVertexRow(std::vector<float> &&row) {
	if (row.size() != cols) {
		return;
	}
	// std::copy_if(std::make_move_iterator(row.begin()),
	// std::make_move_iterator(row.end()), std::back_insert_iterator(Vertices), []
	// { return true; });
	for (auto it : row) {
		Vertices.push_back(it);
	}
}
void EvoSim::VertexArray::PushIndexRow(std::vector<uint32_t> &&indexRow) {
	for (auto it : indexRow) {
		Indices.push_back(it);
	}
}
std::size_t EvoSim::VertexArray::VertexSizeBytes() const {
	return sizeof(float) * Vertices.size();
}
const float *EvoSim::VertexArray::VertexData() const { return Vertices.data(); }
void EvoSim::VertexArray::BufferStaticData() {
	glBindVertexArray(StaticVAO);

	glBindBuffer(GL_ARRAY_BUFFER, StaticVBO);
	std::cout << "vertex size: " << this->VertexSizeBytes() << std::endl;
	glBufferData(GL_ARRAY_BUFFER, this->VertexSizeBytes(), this->VertexData(),
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StaticEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->IndexSizeBytes(),
				 this->IndexData(), GL_STATIC_DRAW);

	std::cout << "cols: " << cols << std::endl;
	for (int i = 0; i < attribPoints.size(); i++) {
		std::cout << "i: " << i << " "
				  << (i == attribPoints.size() - 1
						  ? cols - attribPoints[i]
						  : attribPoints[i + 1] - attribPoints[i])
				  << " " << attribPoints[i]
				  << std::endl;

		glVertexAttribPointer(
			i,
			i == attribPoints.size() - 1 ? cols - attribPoints[i]
										 : attribPoints[i + 1] - attribPoints[i],
			GL_FLOAT, GL_FALSE, cols * sizeof(float),
			(void *)(attribPoints[i] * sizeof(float)));
		glEnableVertexAttribArray(i);
	}

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(2 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EvoSim::VertexArray::AllocateDynamicVa(std::size_t size) {
	glGenVertexArrays(1, &DynamicVAO);
	glGenBuffers(1, &DynamicVBO);
	glGenBuffers(1, &DynamicEBO);
	glBindVertexArray(DynamicVAO);
	glBindBuffer(GL_ARRAY_BUFFER, DynamicVBO);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
std::size_t EvoSim::VertexArray::IndexSizeBytes() const {
	return sizeof(uint32_t) * Indices.size();
}
const uint32_t *EvoSim::VertexArray::IndexData() const {
	return Indices.data();
}
