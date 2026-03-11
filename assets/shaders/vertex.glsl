#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;

uniform float time;
uniform float speed = 5.0;

out vec3 color;
out vec2 uv;

void main(){
	float dx = 0.3;
	float offsetX = sin(time*speed) * dx;

	float scale = 1.0/time;

	//gl_Position = vec4((aPos.x + offsetX)*scale,aPos.y*scale,aPos.z*scale,1.0);
	gl_Position = vec4(aPos*scale,1.0);
	color = aColor;
	uv = aUv;
}