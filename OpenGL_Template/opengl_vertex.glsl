#version 400

//-----------------------------------------------------------------------------
// VERTEX SHADER
//-----------------------------------------------------------------------------

// Inputs //
in vec3 vertex;

// Output // To FragmentShader //
out vec3 fragVertexNormal;
out vec3 fragVertexPosition;
out vec3 fragCamPosition;
out vec3 fragRawVertexPosition;

// Uniform Camera //
uniform mat4 camProjectionMatrix;
uniform mat4 camViewMatrix;
uniform vec3 camPosition;

// Uniform Object //
uniform mat4 objTransformMatrix;

//-----------------------------------------------------------------------------
// VERTEX SHADER MAIN
//-----------------------------------------------------------------------------
void main()
{
    
    mat4 worldViewMatrix = camViewMatrix * objTransformMatrix;
    vec4 objVertexPosition = worldViewMatrix * vec4(vertex, 1.0);
    gl_Position = camProjectionMatrix * objVertexPosition;

    mat4 worldNormal = inverse(worldViewMatrix);
    vec4 vertexNormal = vec4(normalize(vertex.xyz), 0.0);
    fragVertexNormal = (transpose(worldNormal) * vertexNormal).xyz;

    fragVertexPosition = objVertexPosition.xyz;

    fragCamPosition = camPosition;
    fragRawVertexPosition = vertex;
}
