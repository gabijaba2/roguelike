#version 330 core

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in uint tilePosX;
layout(location = 2) in uint tilePosY;
layout(location = 3) in uint tileCharacterId;
layout(location = 4) in uint tileColor;

uniform vec2 screenSize;
uniform vec2 tileScreenSize;

uniform vec2 atlasSize;
uniform vec2 tileAtlasSize;

flat out uint color;
out vec2 uv;

void main()
{
	// tile top left corner pos + quad vert scaled by tileSize
	vec2 worldVertPos = (vec2(tilePosX, tilePosY) * tileScreenSize) + (vertexPos * tileScreenSize);

	vec2 finalVertPos = (worldVertPos / screenSize) * 2.0 - 1.0;
	finalVertPos.y = -finalVertPos.y;	

	gl_Position = vec4(finalVertPos, 0.0, 1.0);
	color = tileColor;	

	vec2 atlasOffset = vec2(0.0, float(tileCharacterId)) * tileAtlasSize;
	uv = (atlasOffset + vertexPos * tileAtlasSize) / atlasSize;

}
