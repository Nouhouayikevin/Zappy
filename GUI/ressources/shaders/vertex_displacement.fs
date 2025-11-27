#version 330

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 viewDir;
in float height;

uniform samplerCube skybox1;       // Texture de ciel actuelle
uniform samplerCube skybox2;       // Texture de ciel suivante
uniform float blendFactor;         // Facteur de mélange (0.0 à 1.0)

uniform vec3 lightColor;
uniform vec3 lightPos;


out vec4 finalColor;

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 V = normalize(viewDir);

    vec4 baseWaterColor = mix(vec4(0.0, 0.1, 0.15, 1.0), vec4(0.1, 0.3, 0.4, 1.0), height);

    
    vec3 reflectDir = reflect(-V, normal);
    
    
    vec4 reflectionColor1 = texture(skybox1, reflectDir);
    vec4 reflectionColor2 = texture(skybox2, reflectDir);
    
    
    vec4 reflectionColor = mix(reflectionColor1, reflectionColor2, blendFactor);

    vec3 L = normalize(lightPos - fragPosition);
    vec3 H = normalize(L + V);
    float specAngle = max(dot(H, normal), 0.0);
    float shininess = 256.0;
    float specularStrength = pow(specAngle, shininess);
    vec3 specularColor = specularStrength * lightColor;

    float fresnelFactor = 0.02 + 0.98 * pow(1.0 - max(0.0, dot(V, normal)), 5.0);

    vec3 waterMixed = mix(baseWaterColor.rgb, reflectionColor.rgb, fresnelFactor);

    finalColor = vec4(waterMixed + specularColor, 1.0);
}