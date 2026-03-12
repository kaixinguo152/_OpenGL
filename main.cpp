#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include<iostream>
#include"glframework/core.h"
#include"glframework/shader.h"
#include<assert.h>
#include"wrapper/checkError.h"
#include"application/application.h"
#include"glframework/texture.h"

GLuint vao_triangle, vao_square;
Shader* shader = nullptr;
Texture* texture = nullptr;
glm::mat4 transform(1.0);

Texture* grassTexture = nullptr;
Texture* landTexture = nullptr;
Texture* noiseTexture = nullptr;

float angle = 0.0f;
void doRotattion() {
	angle += 0.2f;
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void preTransform() {
	transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
}

void doTransform() {
	//float angle = 1.0f;
	//transform = glm::identity<glm::mat4>();
	//transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));  

	float angle = 1.0f;
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void doTranslationTransform() {
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
}

void doScaleTransform() {
	transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
}

void prepareInterleavedBuffer() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	GLuint vbo;
	glGenVertexArrays(1, &vao_triangle);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao_triangle);
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

	float uvs[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};

	GLuint posVbo, colorVbo, uvVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao_triangle);
	glBindVertexArray(vao_triangle);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
}

void prepareVao_square() {
	float positions[] = {
		 -0.5f, -0.5f, 0.0f,
		 0.5f,  -0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2
	};

	float uvs[] = {
		 0.5f, 0.0f, 0.0f,
		 1.0f, 0.0f, 0.0f,
		 0.5f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f
	};

	GLuint posVbo, uvVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao_square);
	glBindVertexArray(vao_square);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareShader_square() {
	shader = new Shader("assets/shaders/vertex_square.glsl", "assets/shaders/fragment_square.glsl");
};

void prepareTexture() {
	texture = new Texture("./assets/textures/texture.jpeg", 0);
}

void prepareTexture_square() {
	grassTexture = new Texture("./assets/textures/grass.jpeg", 0);
	landTexture = new Texture("./assets/textures/land.jpeg", 1);
	noiseTexture = new Texture("./assets/textures/noise.png", 2);
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	shader->begin();

	shader->setFloat("time", glfwGetTime());
	//shader->setInt("grassSampler", 0);
	//shader->setInt("landSampler", 1);
	//shader->setInt("noiseSampler", 2);

	shader->setInt("Sampler", 0);
	shader->setFloat("width", texture->getWidth());
	shader->setFloat("height", texture->getHeight());
	shader->setMatrix("transform", transform);

	glBindVertexArray(vao_triangle);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glBindVertexArray(vao_square);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);

	shader->end();
}

int main(void) {
	glm::vec2 v0(0);
	glm::vec3 v1(0);
	glm::vec4 v2(0);

	glm::vec4 v = v2 + glm::vec4(0);

	glm::mat2x3 mm4(1.0);
	std::cout << glm::to_string(mm4) << std::endl;


	app->init(750, 750);

	//prepareVao_square();
	//prepareShader_square();
	//prepareTexture_square();

	prepareVAO();
	prepareShader();
	prepareTexture();

	glViewport(0, 0, app->getWindowWidth(), app->getWindowHeight());
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	//doTransform();
	//doTranslationTransform();
	//doScaleTransform(); 
	preTransform();
	while (app->update()) {
		doTransform();
		render();
	}

	delete texture;
	app->destroy();
	return 0;
}