#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<assert.h>
#include"wrapper/checkError.h"
#include"application/application.h"

void prepareShader() {
	const char* vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	int success = 0;
	char infoLog[1024];
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED --VERTAX\n" << infoLog << std::endl;
	}

	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED  --FRAGMENT\n" << infoLog << std::endl;
	}
}

int main(void) {
	std::cout << "Hello, World!" << std::endl;

	app->init(1000, 800);

	prepareShader();

	glViewport(0, 0, app->getWindowWidth(), app->getWindowHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (app->update()) {
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	app->destroy();
	return 0;
}