#pragma once

#include<iostream>
#include <cstdint>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#define app Application::getInstance()

class GLFWwindow;

using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);

class Application {
public:
	~Application();

	static Application* getInstance();

	bool init(const int& width, const int& height);

	bool update();

	void destroy();

	uint32_t getWindowWidth() const { return mWindowWidth; }
	uint32_t getWindowHeight() const { return mWindowHeight; }

	void setMouseCallback(MouseCallback callback) { mMouseCallback = callback; }
	void setCursorCallback(CursorCallback callback) { mCursorCallback = callback; }

private:
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
private:
	Application();
	static Application* mInstance;

	GLFWwindow* mWindow = nullptr;

	uint32_t mWindowWidth = 1000;
	uint32_t mWindowHeight = 800;

	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
};