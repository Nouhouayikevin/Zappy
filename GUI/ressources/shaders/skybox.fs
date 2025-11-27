#version 330

in vec3 fragPosition;

uniform samplerCube environmentMap;
uniform samplerCube environmentMap2;
uniform bool vflipped;
uniform bool doGamma;
uniform float rotationAngle; 
uniform float blendFactor; 

out vec4 finalColor;

mat3 rotationY(float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    return mat3(
        cosA, 0.0, sinA,
        0.0, 1.0, 0.0,
       -sinA, 0.0, cosA
    );
}

mat3 rotationZ(float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    return mat3(
        cosA, -sinA, 0.0,
        sinA,  cosA, 0.0,
        0.0,   0.0, 1.0
    );
}

void main()
{
    mat3 rotateY = rotationY(rotationAngle);
    vec3 rotatedDirection = rotateY * fragPosition;

    vec3 color = vec3(0.0);
    vec3 color2 = vec3(0.0);

    if (vflipped) {
        color = texture(environmentMap, vec3(rotatedDirection.x, -rotatedDirection.y, rotatedDirection.z)).rgb;
        color2 = texture(environmentMap2, vec3(rotatedDirection.x, -rotatedDirection.y, rotatedDirection.z)).rgb;
    } else {
        color = texture(environmentMap, rotatedDirection).rgb;
        color2 = texture(environmentMap2, rotatedDirection).rgb;
    }
    float blend = clamp(blendFactor, 0.0, 1.0);
    blend = blend * blend * (3.0 - 2.0 * blend); // ease in-out
    color = mix(color, color2, blend);


    if (doGamma) {
        color = color / (color + vec3(1.0));
        color = pow(color, vec3(1.0/2.2));
    }
    finalColor = vec4(color, 1.0);
}