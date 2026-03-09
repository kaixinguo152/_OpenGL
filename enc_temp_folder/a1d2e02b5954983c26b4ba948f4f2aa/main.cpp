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

void prepareVAO() {
	float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	GLuint posVbo, colorVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
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
	shader->setFloat("time", glfwGetTime());

	shader->end();
}

int main(void) {
	std::cout << "Hello, World!" << std::endl;

	app->init(800, 600);

	prepareVAO();
	prepareShader();

	glViewport(0, 0, app->getWindowWidth(), app->getWindowHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (app->update()) {
		render();
	}

	app->destroy();
	return 0;
}