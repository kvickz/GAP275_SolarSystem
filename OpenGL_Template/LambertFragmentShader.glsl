#version 400

in vec3 vertexNormalOut;
in vec3 vertexPositionOut;
in vec3 fragNormal;

in vec2 fragUV;

in mat4 fragWorldMatrix;

out vec4 colorRGBA;
uniform vec4 objectColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D objectTexture;
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 lightPosition = vec3(0, 1, 0);
uniform vec3 materialAmbient = vec3(0.01);
uniform vec3 materialDiffuse = vec3(0.8, 0.5, 0.5);

void main() {
	//This is starting to work, I just need to convert the light postition to world space
	//vec3 L = normalize(lightPosition.xyz - vertexPositionOut.xyz);

	vec3 L = normalize(vertexPositionOut.xyz - lightPosition.xyz);
	vec3 N = normalize(vertexNormalOut);
	//vec3 N = fragNormal;
	float lightAmount = max(dot(N, L), 0);
	vec3 diffuse = materialDiffuse * lightColor * lightAmount;

	colorRGBA = vec4(diffuse + materialAmbient, 1.0);
//  colorRGBA = vec4(vertexColorOut, 1.0) * objectColor;
//    colorRGBA = vec4(texture(objectTexture, vertexColorOut.xy).xyz, 1.0);

	// Cosine of the angle between the normal and the light direction
	// clamped above 0
	//	- light is at the vertical of the triangle -> 1
	//	- light is perpendicular to the triangle -> 0

	/*
	float cosTheta = clamp( dot(vertexNormal, L), 0, 1);

	colorRGBA = materialDiffuse * lightColor * cosTheta / (distance * distance);
	*/
}
