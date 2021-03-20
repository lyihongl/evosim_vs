#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <cstdlib>
#include <ctime>

#include "../inc/shader.h"
#include "../inc/vertex.h"
#include "../inc/render_engine.h"
#include "../inc/circle.h"
#include "../inc/logging.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

struct DeleteGLFWwindow {
	void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
};

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

int main() {
	// glfw: initialize and configure
	// ------------------------------
	/*
	EvoSim::VertexArray<int> test{};
	test.SetOffsets({ 1,2,3 });
	for (int i : test.Offsets) {
		log(i);
	}

	*/
	std::srand(std::time(nullptr));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));

	// glfw window creation
	// --------------------
	std::unique_ptr<GLFWwindow, DeleteGLFWwindow> window =
		std::unique_ptr<GLFWwindow, DeleteGLFWwindow>(
			glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "EvoSim", NULL, NULL));
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window.get());
	//glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("./src/shaders/test.vert", "./src/shaders/test.frag");
	EvoSim::VertexArray<float> va;
	va.SetOffsets(2, { 0,2,5 });
	EvoSim::VertexManager vm{};

	vm.CreateArrayObj("testVertices");
	vm.CreateBufferObj("vBuf");
	vm.CreateBufferObj("eBuf");
	log(vm.VertexArrayObjects.find("testVertices")->second);
	log(vm.VertexArrayBuffers.find("vBuf")->second);
	//log(vm.VertexElementBuffers.find("eBuf")->second);

	for (auto it : va.Data) {
		log("data " << it);
	}

	std::vector<glm::vec2> positions;
	std::vector<glm::vec3> colors;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			positions.push_back({ (float)i * 30+300, (float)j * 30 + 300});
			colors.push_back({ (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX });
			log(colors.back().x);
			log(positions.back().x);
		}
	}
	vm.CreateBufferObj("vInst", sizeof(glm::vec2)*100);
	vm.CreateBufferObj("vInstColor", sizeof(glm::vec3)*100);
	//glBindBuffer(GL_ARRAY_BUFFER, vm.GetArrayBuffer("vInst"));
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, nullptr, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, vm.GetArrayBuffer("vInstColor"));
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 100, nullptr, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	va.AddData({ 10, -10});
	va.AddData({ -10, -10});
	va.AddData({ -10, 10});
	va.AddData({ 10, 10});
	//va.AddData({ 0.1f, -0.1f});
	//va.AddData({ -0.1f, -0.1f});
	//va.AddData({ -0.1f, 0.1f});
	//va.AddData({ 0.1f, 0.1f});

	unsigned int indices[] = {
		0,1,2,2,3,0
	};
	log("indices:" << sizeof(indices));

	glBindVertexArray(vm.VertexArrayObjects.find("testVertices")->second);
	glBindBuffer(GL_ARRAY_BUFFER, vm.VertexArrayBuffers.find("vBuf")->second);
	glBufferData(GL_ARRAY_BUFFER, va.Data.size() * sizeof(float), va.Data.data(), GL_STATIC_DRAW);
	log("va size:" << va.Data.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vm.GetArrayBuffer("eBuf"));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	log("cols" << va.Cols);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, va.Cols * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vm.GetArrayBuffer("vInst"));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vm.GetArrayBuffer("vInstColor"));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);


	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, va.Cols * sizeof(float), (void*)(2 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, va.Cols * sizeof(float), (void*)(5 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//testVertices.PushVertexRow({0.4f, -0.1f, 1.0f, 0, 0, 0.3f, 0});
	//testVertices.PushVertexRow({0.2f, -0.1f, 1.0f, 0, 0, 0.3f, 0});
	//testVertices.PushVertexRow({0.2f, 0.1f, 1.0f, 0, 0, 0.3f, 0});
	//testVertices.PushVertexRow({0.4f, 0.1f, 1.0f, 0, 0, 0.3f, 0});

	//testVertices.PushVertexRow({0.4f, -0.1f});
	//testVertices.PushVertexRow({0.2f, -0.1f});
	//testVertices.PushVertexRow({0.2f, 0.1f});
	//testVertices.PushVertexRow({0.4f, 0.1f});

	//testVertices.PushIndexRow({0, 1, 2, 2, 3, 0});
	//testVertices.PushIndexRow({4, 5, 6, 6, 7, 4});

	//testVertices.BufferStaticData();

	unsigned int scaleLoc = glGetUniformLocation(shader.ID, "scale");
	unsigned int orthoLoc = glGetUniformLocation(shader.ID, "ortho");

	// render loop
	// -----------

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 scale;
	glm::vec3 scaleVec(1.0f, 16.0f / 9.0f * 0.2f, 0.5f);
	while (!glfwWindowShouldClose(window.get())) {
		// input
		// -----
		//positions[51].x += 1;
		//log(positions[51].x);
		//glBindVertexArray(vm.GetArrayObject("testVertices"));
		glBindBuffer(GL_ARRAY_BUFFER, vm.GetArrayBuffer("vInst"));
		glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size() * sizeof(glm::vec2), positions.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vm.GetArrayBuffer("vInstColor"));
		glBufferSubData(GL_ARRAY_BUFFER, 0, colors.size() * sizeof(glm::vec3), colors.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);
		processInput(window.get());

		scaleVec[1] = (float)(m_viewport[2]) / (float)(m_viewport[3]);
		scale = glm::scale(trans, scaleVec);

		glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scale));

		glm::mat4 orthoProjection = glm::ortho(0.0f, (float)(m_viewport[2]), 0.0f, (float)(m_viewport[3]));
		glUniformMatrix4fv(orthoLoc, 1, GL_FALSE, glm::value_ptr(orthoProjection));
		

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		//EvoSim::RenderDynamicVertexArray(testVertices, shader);
		//glBindVertexArray(testVertices.VAO);
		//shader.use();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		shader.use();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//	glBindVertexArray(dat.DynamicVAO);
		glBindVertexArray(vm.VertexArrayObjects.find("testVertices")->second);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 100);
		//    glBindVertexArray(0);
		glDisable(GL_BLEND);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
		// etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window.get());
		glfwPollEvents();
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(16ms);
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}