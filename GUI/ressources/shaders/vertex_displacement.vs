#version 330


in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;


uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
uniform vec3 cameraPosition; 

uniform float time; 
uniform sampler2D perlinNoiseMap;


out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 viewDir;
out float height;

void main()
{
    
    float speed1 = 0.8;      
    float frequency1 = 0.1;  
    float strength1 = 7.0;  
    
    vec2 animatedTexCoord1 = sin(vertexTexCoord + vec2(sin(time * speed1 + vertexPosition.x * frequency1), cos(time * speed1 + vertexPosition.z * frequency1)) * 0.3);
    animatedTexCoord1 = animatedTexCoord1 * 0.5 + 0.5;
    float displacement1 = texture(perlinNoiseMap, animatedTexCoord1).r * strength1;

    
    float speed2 = 2.5;      
    float frequency2 = 0.8;  
    float strength2 = 1.5;   
    
    
    vec2 animatedTexCoord2 = sin(vertexTexCoord * 2.0 + vec2(sin(time * speed2 + vertexPosition.x * frequency2), cos(time * speed2 + vertexPosition.z * frequency2)) * 0.5);
    animatedTexCoord2 = animatedTexCoord2 * 0.5 + 0.5;
    float displacement2 = texture(perlinNoiseMap, animatedTexCoord2).r * strength2;
    
    float totalDisplacement = displacement1 + displacement2;

    
    vec3 displacedPosition = vertexPosition + vec3(0.0, totalDisplacement, 0.0);

    
    fragPosition = vec3(matModel*vec4(displacedPosition, 1.0));
    fragTexCoord = vertexTexCoord;
    
    
    
    vec3 neighbor1 = vertexPosition + vec3(1.0, 0.0, 0.0);
    vec3 neighbor2 = vertexPosition + vec3(0.0, 0.0, 1.0);
    
    vec3 displacedNeighbor1 = neighbor1 + vec3(0.0, displacement1 + displacement2, 0.0);
    vec3 displacedNeighbor2 = neighbor2 + vec3(0.0, displacement1 + displacement2, 0.0);
    vec3 tangent = normalize(displacedNeighbor1 - displacedPosition);
    vec3 bitangent = normalize(displacedNeighbor2 - displacedPosition);
    vec3 calculatedNormal = cross(bitangent, tangent);
    fragNormal = normalize(vec3(matNormal*vec4(calculatedNormal, 1.0)));
    
    height = displacedPosition.y * 0.1;
    viewDir = cameraPosition - fragPosition;

    gl_Position = mvp*vec4(displacedPosition, 1.0);
}

//joseph
// une mer de tempête : Augmente strength1 (ex: 15.0) et strength2 (ex: 2.5).
// un lac calme : Diminue fortement strength1 (ex: 2.0) et strength2 (ex: 0.5).
// des vagues plus rapides : Augmente speed1 et speed2.
// des vagues plus larges ou plus serrées : Modifie frequency1 et frequency2.
