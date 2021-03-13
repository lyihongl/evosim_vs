#include "../inc/render_engine.h"
#include "../inc/logging.h"
//void EvoSim::RenderStaticVertexArray(const VertexArray& dat, const Shader& shader) {
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    shader.use();
//	glBindVertexArray(dat.StaticVAO);
//	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//    glDisable(GL_BLEND);
//    //glUseProgram(0);
//}
//
//void EvoSim::RenderDynamicVertexArray(const VertexArray& dat, const Shader& shader) {
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    shader.use();
//	glBindVertexArray(dat.DynamicVAO);
//	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//    glDisable(GL_BLEND);
//}

EvoSim::VertexManager::VertexManager() {
}

void EvoSim::VertexManager::CreateArrayObj(GLuint& id) {
	glGenVertexArrays(1, &id);
	log("created VAO with id: " << id);
}

void EvoSim::VertexManager::CreateBufferObj(GLuint& id) {
	glGenBuffers(1, &id);
}

void EvoSim::VertexManager::CreateArrayObj(std::string name) {
	if (this->VertexArrayObjects.find(name) != this->VertexArrayObjects.end()) {
		log("Vertex array object already exists");
		return;
	}
	CreateArrayObj(this->VertexArrayObjects[name]);
}

void EvoSim::VertexManager::CreateBufferObj(std::string name, BufferType type) {
	if (type == BufferType::Vertex) {
		if (this->VertexArrayBuffers.find(name) != this->VertexArrayBuffers.end()) {
			log("Vertex array buffer already exists");
			return;
		}
		CreateBufferObj(this->VertexArrayBuffers[name]);
	}
	else {
		if (this->VertexElementBuffers.find(name) != this->VertexElementBuffers.end()) {
			log("Vertex array buffer already exists");
			return;
		}
		CreateBufferObj(this->VertexElementBuffers[name]);
	}
}

GLuint EvoSim::VertexManager::GetElementBuffer(std::string name) {
	return this->VertexElementBuffers.find(name)->second;
}

GLuint EvoSim::VertexManager::GetArrayBuffer(std::string name) {
	return this->VertexArrayBuffers.find(name)->second;
}

GLuint EvoSim::VertexManager::GetArrayObject(std::string name) {
	return this->VertexArrayObjects.find(name)->second;
}
