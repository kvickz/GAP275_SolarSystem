#version 400

//-------------------------------------------------------------------------------------- -
//	Attributes
//-------------------------------------------------------------------------------------- -
in vec3 fragVertexPosition;
in vec3 fragVertexNormal;
//in vec2 fragUV;

in vec2 fragTextureCoordinate;

out vec4 colorRGBA;
uniform vec4 objectColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D objectTexture;
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 lightPosition = vec3(0, 0, 0);
uniform vec3 materialAmbient = vec3(0.01);
uniform vec3 materialDiffuse = vec3(0.8, 0.5, 0.5);

// Texture //

in mat4 fragWorldMatrix;

//-------------------------------------------------------------------------------------- -
//	Main
//-------------------------------------------------------------------------------------- -
void main() {
	
	//Direction of Light
	//vec3 L = normalize(fragVertexPosition - lightPosition);
	vec3 L = normalize(lightPosition - fragVertexPosition);
	//vec3 L = normalize(vertexPositionOut.xyz - worldLightPosition.xyz);

	//Surface Normal
	vec3 N = normalize(fragVertexNormal);
	//vec3 N = fragNormal;

	//Dot product of Direction of light and the surface normal
	//or, ratio of the angle between the normal and the light source from 0 to 1
	float lightAmount = max(dot(N, L), 0);

	//Get Texture coordinates
	vec4 textureFinal = texture(objectTexture, fragTextureCoordinate);

	//Calculate the diffuse value
	vec3 diffuse = materialDiffuse * lightColor * lightAmount * textureFinal.xyz;

	//Calculate the output value
	colorRGBA = vec4(diffuse + materialAmbient, 1.0);
//  colorRGBA = vec4(vertexColorOut, 1.0) * objectColor;
//  colorRGBA = vec4(texture(objectTexture, vertexColorOut.xy).xyz, 1.0);
}