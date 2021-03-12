#include "../inc/render_engine.h"
void EvoSim::RenderVertexArray(const VertexArray& dat, const Shader& shader) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.use();
	glBindVertexArray(dat.StaticVAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    //glUseProgram(0);
}
