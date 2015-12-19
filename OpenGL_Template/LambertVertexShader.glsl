#version 400

//-------------------------------------------------------------------------------------- -
//	Attributes
//-------------------------------------------------------------------------------------- -
// Vertex Attributes //
in vec3 vertex;
in vec3 vertexColor;
//in vec3 vertexNormal;

// UVS //
in vec2 vertTextureCoordinate;
//in vec2 vertUV;

// Output Variables //
out vec3 fragVertexPosition;
out vec3 fragVertexNormal;
//out vec2 fragUV;
//out vec3 fragCameraPosition;

out vec2 fragTextureCoordinate;

// Uniforms //
uniform mat4 transformMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform vec3 cameraPosition;

//-------------------------------------------------------------------------------------- -
//	Main
//-------------------------------------------------------------------------------------- -
void main() 
{
	mat4 worldViewMatrix = viewMatrix * transformMatrix;
	vec4 vertexPosition = worldViewMatrix * vec4(vertex, 1.0);
	gl_Position = projectionMatrix * vertexPosition;
	
	//vertexNormalOut = (transpose(worldViewMatrix) * vec4(normalize(vertex.xyz), 0)).xyz;
	//vec4 normal = transpose(inverse(transformMatrix)) * vec4(normalize(vertex.xyz), 0);
	mat4 worldNormal = inverse(worldViewMatrix);
	vec4 vertexNormal = vec4(normalize(vertex.xyz), 0.0);
	fragVertexNormal = (transpose(worldNormal) * vertexNormal).xyz;

	fragVertexPosition = vertexPosition.xyz;


	fragTextureCoordinate = vertTextureCoordinate;
	//fragUV = vertUV;
	//fragPosition = vertex;
	//fragCameraPosition = cameraPosition;
}