#version 400

layout (location = 0) in vec3 position;

uniform mat4 transformMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform mat4 transformViewProjectionMatrix = mat4(1.0);

void main()
{
	gl_Position = transformViewProjectionMatrix * vec4(position, 1.0);
}