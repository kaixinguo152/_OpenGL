#include<iostream>
#include"glframework/core.h"
#include"glframework/shader.h"
#include<assert.h>
#include"wrapper/checkError.h"
#include"application/application.h"

GLuint vao;
Shader* shader = nullptr;

void prepareInterleavedBuffer() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	shader->begin();

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	//glBindVertexArray(0);

	shader->end();
}

int main(void) {
	std::cout << "Hello, World!" << std::endl;

	app->init(800, 600);

	prepareInterleavedBuffer();
	prepareShader();

	glViewport(0, 0, app->getWindowWidth(), app->getWindowHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (app->update()) {
		render();
	}

	app->destroy();
	return 0;
}