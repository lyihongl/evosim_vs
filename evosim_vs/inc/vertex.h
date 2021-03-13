#ifndef VERTEX_H
#define VERTEX_H
#include <glad/glad.h>
#include <functional>
#include <iostream>
#include <vector>
#include <optional>

namespace EvoSim {

template<typename T>
struct VertexArray {
	VertexArray();
	std::vector<std::size_t> Offsets;
	std::vector<T> Data;
	std::size_t Cols;
	void SetOffsets(std::size_t cols, std::vector<std::size_t>&& offsets);
	void AddData(std::vector<T>&& data);
	/*
	unsigned int StaticVAO, StaticVBO, StaticEBO, DynamicVAO, DynamicVBO, DynamicEBO;
	std::size_t cols;
	std::size_t DynamicBufferFill;
	std::vector<std::size_t> attribPoints;
	VertexArray(const std::size_t cols, const std::vector<std::size_t> &&attribPoints);
	VertexArray(const std::size_t cols, const std::vector<std::size_t> &attribPoints);
	std::vector<float> Vertices;
	std::vector<uint32_t> Indices;
	const std::size_t GetRows();
	void PushVertexRow(std::vector<float> &&row);
	void PushIndexRow(std::vector<uint32_t> &&indexRow);
	void BufferStaticData();
	void AllocateDynamicVa(std::size_t size);
	void BufferDynamicData(std::optional<std::size_t> index = std::nullopt);
	std::size_t VertexSizeBytes() const;
	const float *VertexData() const;

	std::size_t IndexSizeBytes() const;
	const uint32_t *IndexData() const;
	*/
};
template<typename T>
inline VertexArray<T>::VertexArray() {
}
template<typename T>
inline void VertexArray<T>::SetOffsets(std::size_t cols, std::vector<std::size_t>&& offsets) {
	this->Cols = cols;
	this->Offsets = std::move(offsets);
}
template<typename T>
inline void VertexArray<T>::AddData(std::vector<T>&& data) {
	this->Data.insert(std::end(this->Data), std::begin(data), std::end(data));
}
};	// namespace EvoSim

#endif
