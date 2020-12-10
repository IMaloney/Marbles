#version 330 core

in vec3 vertex;                 // The position of the vertex, in camera space!
in vec3 vertexToCamera;         // Vector from the vertex to the eye, which is the camera
in vec3 eyeNormal;	        // Normal of the vertex, in camera space!

uniform float r0;		// The R0 value to use in Schlick's approximation
uniform float eta1D;		// The eta value to use initially
uniform vec3  eta;              // Contains one eta for each channel (use eta.r, eta.g, eta.b in your code)

uniform mat4 view;
uniform mat4 model;

uniform samplerCube envMap;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(eyeNormal);
    vec3 cameraToVertex = normalize(vertex); //remember we are in camera space!
    vec3 vertexToCamera = normalize(vertexToCamera);
    // TODO: fill the rest in

    mat4 matrix = inverse(view*model); // inverse(view*model)

    // Getting reflection color
    vec3 r = reflect(cameraToVertex, n);
    vec4 r2 = vec4(r[0], r[1], r[2], 0);
    vec4 worldR = matrix * r2; // ???
    vec3 finalR = vec3(worldR[0], worldR[1], worldR[2]);
    finalR = normalize(finalR);

    vec4 reflectColor = texture(envMap, finalR);

    vec3 redDir = refract(cameraToVertex, n, eta.r);
    vec3 greenDir = refract(cameraToVertex, n, eta.g);
    vec3 blueDir = refract(cameraToVertex, n, eta.b);

    vec3 worldRed = (matrix * vec4(redDir.xyz, 0.0f)).rgb; // ???
    vec3 worldGreen = (matrix * vec4(greenDir.xyz, 0.0f)).rgb;
    vec3 worldBlue = (matrix * vec4(blueDir.xyz, 0.0f)).rgb;


//    finalRed = normalize(finalRed);
//    finalGreen = normalize(finalGreen);
//    finalBlue = normalize(finalBlue);

    vec4 refractColorR = texture(envMap, worldRed);
    vec4 refractColorG = texture(envMap, worldGreen);
    vec4 refractColorB = texture(envMap, worldBlue);

    // just sum them all???
    vec4 refract2 = vec4(refractColorR.r, refractColorG.g, refractColorB.b, 1);

    vec3 incident = normalize(vertex - vertexToCamera);

    float thetaI = dot(-incident, eyeNormal);
    float F = r0 + (1.0f - r0)*pow(1.0f - thetaI, 5);

    fragColor = mix(refract2, reflectColor, F);
            //reflectColor;
}
