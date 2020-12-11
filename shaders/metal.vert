#version 330 core

in vec3 position;               // Position in object space
in vec3 normal;                 // Normal in object space

out vec3 vertex;                // Vertex position in camera space
out vec3 vertexToLight;         // Vector from the vertex to the light
out vec3 vertexToCamera;        // Vector from the vertex to the eye, which is the camera
out vec3 eyeNormal;             // Normal in eye space

//// Transformation matrices
uniform mat4 m;             // model matrix
uniform mat4 v;              // view matrix
uniform mat4 p;        // projection matrix

uniform vec4 lightPosition;

void main()
{

    vertex = ((v*m)*(vec4(position, 1.0))).xyz;
    vec4 camLightPosition = v*m*lightPosition;           // Light position in camera space
    vertexToLight = normalize(camLightPosition.xyz - vertex);
    vertexToCamera = -normalize(vertex);
    eyeNormal = normalize(mat3(transpose(inverse(v*m))) * normal);
    gl_Position = p*v*m*(vec4(position,1.0));

}
