#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>

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
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("./src/shaders/test.vert", "./src/shaders/test.frag");
	EvoSim::VertexArray<float> va;
	va.SetOffsets(7, { 0,2,5 });
	EvoSim::VertexManager vm{};

	vm.CreateArrayObj("testVertices");
	vm.CreateBufferObj("vBuf", EvoSim::VertexManager::BufferType::Vertex);
	vm.CreateBufferObj("eBuf", EvoSim::VertexManager::BufferType::Element);
	log(vm.VertexArrayObjects.find("testVertices")->second);
	log(vm.VertexArrayBuffers.find("vBuf")->second);
	log(vm.VertexElementBuffers.find("eBuf")->second);

	//va.AddData({ -0.5f, -0.5f });
	//va.AddData({ 0.5f, -0.5f });
	//va.AddData({ 0.0f, 0.5f });

	for (auto it : va.Data) {
		log("data " << it);
	}

	//glBindVertexArray(vm.VertexArrayObjects.find("testVertices")->second);
	//glBindBuffer(GL_ARRAY_BUFFER, vm.VertexArrayBuffers.find("vBuf")->second);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), va.Data.data(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//EvoSim::Circle c{};
	//EvoSim::VertexArray testVertices(7, EvoSim::Circle::AttribPoints);
	//EvoSim::VertexArray testVertices(7, {0, 2, 5});
	//testVertices.AllocateDynamicVa(1024);
	//c.AddtoVa(testVertices);

	va.AddData({ 0.1f, -0.1f, 1.0f, 0, 0, 0, 0 });
	va.AddData({ -0.1f, -0.1f, 1.0f, 0.5f, 0, 0, 0 });
	va.AddData({ -0.1f, 0.1f, 1.0f, 0, 0, 0, 0 });
	va.AddData({ 0.1f, 0.1f, 1.0f, 0, 1.0f, 0, 0 });

	unsigned int indices[] = {
		0,1,2,2,3,0
	};
	log("indices:" << sizeof(indices));

	glBindVertexArray(vm.VertexArrayObjects.find("testVertices")->second);
	glBindBuffer(GL_ARRAY_BUFFER, vm.VertexArrayBuffers.find("vBuf")->second);
	glBufferData(GL_ARRAY_BUFFER, va.Data.size() * sizeof(float), va.Data.data(), GL_STATIC_DRAW);
	log("va size:" << va.Data.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vm.VertexElementBuffers.find("eBuf")->second);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	log("cols" << va.Cols);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, va.Cols * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, va.Cols * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, va.Cols * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

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

	// render loop
	// -----------

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 scale;
	glm::vec3 scaleVec(9.0f / 16.0f * 0.2f, 1.0f, 0.5f);
	while (!glfwWindowShouldClose(window.get())) {
		// input
		// -----
		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);
		processInput(window.get());

		scaleVec[0] = (float)(m_viewport[3]) / (float)(m_viewport[2]);
		scale = glm::scale(trans, scaleVec);

		glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scale));

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
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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