#pragma once

#include <cstdint>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#define app Application::getInstance()

class GLFWwindow;

class Application {
public:
	~Application();

	static Application* getInstance();

	bool init(const int& width, const int& height);

	bool update();

	void destroy();

	uint32_t getWindowWidth() const { return mWindowWidth; }
	uint32_t getWindowHeight() const { return mWindowHeight; }
private:
	Application();
	static Application* mInstance;

	GLFWwindow* mWindow = nullptr;

	uint32_t mWindowWidth = 1000;
	uint32_t mWindowHeight = 800;
};