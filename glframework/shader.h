#pragma once

#include "core.h"
#include<string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();

	void end();

	void setFloat(const std::string& name, float value) const;

	void setInt(const std::string& name, int value) const;

	void setMatrix4x4(const std::string& name, const glm::mat4& matrix) const;

private:
	void checkCompileErrors(GLuint target, std::string type);

private:
	GLuint mProgram{ 0 };

};