#version 330 core

in vec3 vertex;                 // The position of the vertex, in camera space
in vec3 vertexToLight;          // Vector from the vertex to the light
in vec3 vertexToCamera;            // Vector from the vertex to the eye
in vec3 eyeNormal;		// Normal of the vertex, in camera space

uniform samplerCube envMap;	// The cube map containing the environment to reflect
uniform vec4 ambient;		// The ambient channel of the color to reflect
uniform vec4 diffuse;		// The diffuse channel of the color to reflect
uniform vec4 specular;		// The specular channel of the color to reflect

uniform mat4 model;             // model matrix
uniform mat4 view;              // view matrix
uniform mat4 mvp;               // model view projection matrix

uniform float r0;		// The Fresnel reflectivity when the incident angle is 0
uniform float m;		// The roughness of the material

out vec4 fragColor;

void main()
{
    vec3 n = normalize(eyeNormal);
    vec3 l = normalize(vertexToLight);
    vec3 cameraToVertex = normalize(vertex); //remember we are in camera space!
    vec3 v = normalize(vertexToCamera);

    vec3 h = normalize(vertexToLight + vertexToCamera);
    float alpha = acos(dot(n, h));

    // Beckmann distribution factor
    float D = exp(-pow(tan(alpha), 2)/pow(m, 2))/(4.0f*pow(m, 2)*pow(cos(alpha), 4));

    // ANGLE CALCULATION MAY BE SUS
//    float thetaI = acos(dot(normalize(eyeNormal), cameraToVertex));
    float thetaI = dot(normalize(eyeNormal), -cameraToVertex); /// it was supposed to be negative????
//    float F = r0 + (1.0f - r0)*pow(1.0f - cos(thetaI), 5);
    float F = r0 + (1.0f - r0)*pow(1.0f - thetaI, 5);

    // geometric attenuation term
    float min1 = (2.0f*dot(h, n)*dot(v, n))/dot(v, h);
    float min2 = (2.0f*dot(h, n)*dot(l, n))/dot(v, h);
    float G = min(1.0f, min(min1, min2));

    //k specular
    float kS = D*F*G/dot(v, n);
    kS = max(kS, 0);

    // Lambert term???????
    float lambert = max(dot(n, l), 0);
//    float lambert = cos(dot(n, l));

    float red = ambient[0] + lambert * diffuse[0] + kS * specular[0];
    float green = ambient[1] + lambert * diffuse[1] + kS * specular[1];
    float blue = ambient[2] + lambert * diffuse[2] + kS * specular[2];

    vec3 r = reflect(cameraToVertex, n);
    vec4 r2 = vec4(r[0], r[1], r[2], 0);
    vec4 worldR = view*model * r2; // ???

    vec3 finalR = vec3(worldR[0], worldR[1], worldR[2]);
    finalR = normalize(finalR);

    vec4 reflectColor = texture(envMap, finalR);

    red = mix(red, reflectColor[0], F);
            //red * (1.0f - F) + reflectColor[0] * F;
    green =  mix(green, reflectColor[1], F);
            //green * (1.0f - F) + reflectColor[1] * F;
    blue =  mix(blue, reflectColor[2], F);
            //blue * (1.0f - F) + reflectColor[2] * F;

    fragColor = vec4(red, green, blue, 1.0);
            //reflectColor;
            //vec4(red, green, blue, 1.0);
}
