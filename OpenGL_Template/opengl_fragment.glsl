#version 400

// DEFINES //
#define VALUE 50.0
#define LIGHT vec3(VALUE, VALUE, VALUE)
//-----------------------------------------------------------------------------
// FRAGMENT SHADER
//-----------------------------------------------------------------------------

// Input // From VertexShader //
in vec3 fragVertexNormal;
in vec3 fragVertexPosition;
in vec3 fragCamPosition;
in vec3 fragRawVertexPosition;

// Output //
out vec4 colorRGBA;

// Switches //
// uniform float gammaCorrection = 2.2;
uniform float gammaCorrection = 1.0;

// Uniform Light //
uniform vec3 lightPosition = vec3(10.0, 10.0, 0.0);
uniform vec3 lightAmbient  = LIGHT;
uniform vec3 lightDiffuse  = LIGHT;
uniform vec3 lightSpecular = LIGHT;

// Uniform Material //
uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;

//-----------------------------------------------------------------------------
// FRAGMENT SHADER MAIN
//-----------------------------------------------------------------------------
void main()
{
    
    // Calculate Light Direction
    vec3 L = normalize(lightPosition - fragVertexPosition);
    
    // Calculate Surface Normal
    vec3 N = normalize(fragVertexNormal);

    // Calculate Direction to Eye
    vec3 vEyeVector = fragCamPosition - fragRawVertexPosition;
    vec3 V = normalize(vEyeVector);

    // Calculate Halfway Vector
    vec3 H = normalize(L + V);

    // Light Amount / Distance / Attenuation 
    float lightAmount = max(dot(N, L), 0);
    float lightDistance = distance(lightPosition, fragVertexPosition);
    float lightAttCon = 1.0; // Light Attenunation Constant
    float lightAttLin = 1.0 * lightDistance; // Light Attenuation Linear
    float lightAttQua = 2.0 * pow(lightDistance, 2); // Light Attenuation Quadratic
    float lightAttFactor = 0.5; // This is typically 1. I'm controlling the amount of lightAttenuation to apply here.
    float lightAttenuation = lightAttFactor / (lightAttCon + lightAttLin + lightAttQua);
    float finalLight = lightAmount * lightAttenuation;

    // Ambient //
    vec3 ambientLight = lightAmbient * finalLight;
    vec3 finalAmbient = ambientLight * materialAmbient;
    
    //  Diffuse //
    vec3 diffuseLight = lightDiffuse * finalLight;
    vec3 finalDiffuse = diffuseLight * materialDiffuse;


    // Specular //
    vec3 specularLight = lightSpecular * finalLight;
    float materialShininess = 50.0;
    float finalShininess = pow(max(dot(N, H), 0.0), materialShininess);
    vec3 finalSpecular = specularLight * materialSpecular * finalShininess;

    // Output Fragment Color //
    vec3 outputColorLinear = (finalAmbient + (finalDiffuse + finalSpecular));
    vec3 outputColor = pow(outputColorLinear, vec3(1.0/gammaCorrection));

    colorRGBA = vec4(outputColor, 1.0);
    
}

// Comments:
// [???]
// I'm attempting a small GammaCorrection right before the color is being output. Note that
// the GL_FRAMEBUFFER_SRGB flag is also being set in the renderer. Am I achieving anything
// at all here, or are these two things trying to do the same thing? Is what I'm doing bad?
//
