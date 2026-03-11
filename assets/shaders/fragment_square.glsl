#version 460 core
out vec4 FragColor;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;

in vec2 uv;

void main()
{
	vec4 grassColor = texture(grassSampler,uv);
	vec4 landColor = texture(landSampler,uv);
	vec4 noiseColor = texture(noiseSampler,uv);

	float weight = noiseColor.r; // Assuming the noise texture is grayscale, we can use the red channel as the weight

	//vec4 finalColor = grassColor*(1.0-weight) + landColor*weight;
	vec4 finalColor = mix(grassColor, landColor, weight); // Using GLSL's built-in mix function for linear interpolation

	FragColor = vec4(finalColor.rgb, 1.0);
}