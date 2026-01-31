#version 330 core

in vec2 uv;
flat in uint color;
out vec3 pixelColor;

uniform sampler2D texSampler;

vec3 vgaColorPallete[16] = vec3[16](
	vec3(0.0,0.0,0.0),
	vec3(0.0,0.0,0.666),
	vec3(0.0,0.666,0.0),
	vec3(0.0,0.666,0.666),
	vec3(0.666,0.0,0.0),
	vec3(0.666,0.0,0.666),
	vec3(0.666,0.333,0.0),
	vec3(0.666,0.666,0.666),
	vec3(0.333,0.333,0.333),
	vec3(0.333,0.333,1.0),
	vec3(0.333,1.0,0.333),
	vec3(0.333,1.0,1.0),
	vec3(1.0,0.333,0.333),
	vec3(1.0,0.333,1.0),
	vec3(1.0,1.0,0.333),
	vec3(1.0,1.0,1.0)
);

void main()
{
	float atlasValue = texture(texSampler, uv).r;	

	pixelColor = mix(
		vgaColorPallete[(color >> 4u) & 0xFu], 
		vgaColorPallete[color & 0xFu], 
		atlasValue*255
	);
}
