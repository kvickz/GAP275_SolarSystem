#version 400

in vec3 vertex;
in vec3 vertexColor;
in vec3 vertexNormal;

in vec2 vertUV;

out vec3 vertexNormalOut;
out vec3 vertexPositionOut;
out vec3 fragNormal;

out vec2 fragUV;

uniform mat4 transformMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out mat4 fragWorldMatrix;

void main() {
	mat4 worldViewMatrix = viewMatrix * transformMatrix;

	vec4 vertexPosition = worldViewMatrix * vec4(vertex, 1.0);
	gl_Position = projectionMatrix * vertexPosition;

	vertexPositionOut = vertexPosition.xyz;
	vertexNormalOut = (transpose(worldViewMatrix) * vec4(normalize(vertex.xyz), 0)).xyz;

	fragNormal = vertexNormal;
	fragUV = vertUV;

	fragWorldMatrix = worldViewMatrix;
}