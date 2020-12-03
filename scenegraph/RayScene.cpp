#include "RayScene.h"
#include "Settings.h"
#include "CS123SceneData.h"

#include <iostream>
#include <iterator>


RayScene::RayScene(Scene &scene) :
    Scene(scene)
{
}

RayScene::~RayScene()
{
//    m_kdTree.~KDTree();
}

glm::vec4 RayScene::calculateIllumination(CS123ShapeIntersection intersect, int depth) {
    CS123FlatSceneNode node = intersect.node;
    CS123SceneMaterial primMaterial = node.primitive.material;

    glm::vec4 finalVal = m_globalData.ka * primMaterial.cAmbient;
//    float finalVal = primMaterial.cAmbient[rgb]; // IS AMBIENT NORMALIZED OR NOT - CHECK!!!

    for (int i = 0; i < (int) m_lightData.size(); i++) {
        CS123SceneLightData light = m_lightData[i];
        if (light.type == LightType::LIGHT_POINT && m_pointLights) {
            glm::vec4 worldSpacePoint = node.transformation * intersect.point;

            // Distance from intersection point to the light
            float pointToLightLength = sqrt(pow(light.pos.x - worldSpacePoint.x, 2) +
                                      pow(light.pos.y - worldSpacePoint.y, 2) +
                                      pow(light.pos.z - worldSpacePoint.z, 2));
            glm::vec4 pointToLight = glm::normalize(light.pos - worldSpacePoint);

            if (m_shadows) {
                // Check if this light is blocked by an object
                glm::vec4 adjustedPoint = worldSpacePoint + epsilon*pointToLight;

                CS123ShapeIntersection intersection = CS123ShapeIntersection();
                intersection.found = false;

                CS123ShapeIntersection shadow = findShapeIntersect(adjustedPoint, pointToLight);

                if (shadow.found) {
                    glm::vec4 worldSpaceShadow = shadow.node.transformation * shadow.point;
                    float pointToPointLength = sqrt(pow(worldSpaceShadow.x - worldSpacePoint.x, 2) +
                                              pow(worldSpaceShadow.y - worldSpacePoint.y, 2) +
                                              pow(worldSpaceShadow.z - worldSpacePoint.z, 2));
                    if (pointToLightLength > pointToPointLength) {
                        continue;
                    }
                }
            }
            // Outside / to the left of brackets
            glm::vec4 sumAtten = light.color; // intensity of light m for wavelength

            glm::vec3 attenFunc = light.function;
            // 1 / (c1 + c2*d + c3*d^2)
            float attenVal = 1.0f/(attenFunc.x + attenFunc.y*pointToLightLength + attenFunc.z*pow(pointToLightLength, 2));
            attenVal = std::min(1.0f, attenVal);

            sumAtten *= attenVal;

            // Everything after this is inside the brackets of equation
            // Intersect (diffuse)
            glm::vec4 sumDiffuse;

            // If we have turned texture mapping on, and have a texture filename
            if (m_texturesOn && (node.texFilename != "")) {

                QImage texture = m_textures[node.texFilename];

                if (texture.isNull()) {
                    // This means the texture wasn't loaded properly (not on dept. machine likely)
                    sumDiffuse = primMaterial.cDiffuse; // object’s diffuse color for wavelength
                    sumDiffuse *= m_globalData.kd; // global diffuse coefficient
                } else {
                    glm::vec2 st = getTextureCoords(intersect, texture.width(), texture.height());

                    float blend = node.primitive.material.blend;

                    glm::vec4 objDiff = primMaterial.cDiffuse * m_globalData.kd;
                    QColor textDiff = texture.pixelColor(st[0], st[1]);

                    // Divide by 255
                    glm::vec4 texVec = glm::vec4(textDiff.red()/255.0f, textDiff.green()/255.0f, textDiff.blue()/255.0f, 1.0f);

                    sumDiffuse = glm::mix(objDiff, texVec, blend);
                }

            } else {
                sumDiffuse = primMaterial.cDiffuse; // object’s diffuse color for wavelength
                sumDiffuse *= m_globalData.kd; // global diffuse coefficient
            }

            glm::mat3x3 threeMat = glm::mat3x3(node.transformation);
            glm::mat3x3 trans = glm::transpose(glm::inverse(threeMat));

            glm::vec3 surfaceNormal = glm::normalize(trans * glm::vec3(intersect.normal.xyz()));

            glm::vec3 incomingLight = glm::normalize(light.pos.xyz() - worldSpacePoint.xyz());

            sumDiffuse *= glm::clamp(glm::dot(surfaceNormal, incomingLight), 0.0f, 1.0f);

            // Ray additions (specular)
            glm::vec4 sumSpec = primMaterial.cSpecular;
            sumSpec *= m_globalData.ks;

            glm::vec4 reflectionVector = calculateReflectionVector(glm::vec4(surfaceNormal, 0.0f), pointToLight);
            float reflectDot = glm::dot(reflectionVector, -intersect.originalRay); // MAYBE NEGATIVE, MAYBE NOT
            reflectDot = glm::clamp(reflectDot, 0.0f, 1.0f);
            reflectDot = pow(reflectDot, primMaterial.shininess);
            sumSpec *= reflectDot;

            finalVal += sumAtten * (sumDiffuse + sumSpec);
        } else if (light.type == LightType::LIGHT_DIRECTIONAL && m_directionalLights) {
            glm::vec4 worldSpacePoint = node.transformation * intersect.point;

            // Check if this light is blocked by an object
            if (m_shadows) {
                glm::vec4 adjustedPoint = worldSpacePoint + epsilon*-light.dir;

                CS123ShapeIntersection intersection = CS123ShapeIntersection();
                intersection.found = false;

                CS123ShapeIntersection shadow = findShapeIntersect(adjustedPoint, -light.dir);
                if (shadow.found) {
                    continue;
                }
            }

            glm::vec4 sum = light.color; // intensity of light m for wavelength

            // Everything after this is inside the brackets of equation
            // Intersect (diffuse)
            glm::vec4 sumDiffuse;

            // If we have turned texture mapping on, and have a texture filename
            if (m_texturesOn && (node.texFilename != "")) {

                QImage texture = m_textures[node.texFilename];

                if (texture.isNull()) {
                    // This means the texture wasn't loaded properly (not on dept. machine likely)
                    sumDiffuse = primMaterial.cDiffuse; // object’s diffuse color for wavelength
                    sumDiffuse *= m_globalData.kd; // global diffuse coefficient
                } else {
                    glm::vec2 st = getTextureCoords(intersect, texture.width(), texture.height());

                    float blend = node.primitive.material.blend;

                    glm::vec4 objDiff = primMaterial.cDiffuse * m_globalData.kd;
                    QColor textDiff = texture.pixelColor(st[0], st[1]);

                    // Divide by 255
                    glm::vec4 texVec = glm::vec4(textDiff.red()/255.0f, textDiff.green()/255.0f, textDiff.blue()/255.0f, 1.0f);

                    sumDiffuse = glm::mix(objDiff, texVec, blend);
                }

            } else {
                sumDiffuse = primMaterial.cDiffuse; // object’s diffuse color for wavelength
                sumDiffuse *= m_globalData.kd; // global diffuse coefficient
            }

            glm::mat3x3 threeMat = glm::mat3x3(node.transformation);
            glm::mat3x3 trans = glm::transpose(glm::inverse(threeMat));

            glm::vec3 surfaceNormal = glm::normalize(trans * glm::vec3(intersect.normal.xyz()));

            sumDiffuse *= glm::clamp(glm::dot(surfaceNormal, light.dir.xyz()), 0.0f, 1.0f); // HERE

            // Ray additions (specular)
            glm::vec4 sumSpec = primMaterial.cSpecular;
            sumSpec *= m_globalData.ks;

            glm::vec4 reflectionVector = calculateReflectionVector(glm::vec4(surfaceNormal, 0.0f), glm::normalize(-light.dir)); // HERE TOO
            float reflectDot = glm::dot(reflectionVector, -intersect.originalRay); // MAYBE NEGATIVE, MAYBE NOT
            reflectDot = glm::clamp(reflectDot, 0.0f, 1.0f);
            reflectDot = pow(reflectDot, primMaterial.shininess);
            sumSpec *= reflectDot;

            finalVal += sum * (sumDiffuse + sumSpec);
        }
    }

    // Recursive reflection calculation
    if (m_reflection && (depth <= recursionLimit)) {
        glm::vec4 sumReflect = primMaterial.cReflective;
        sumReflect *= m_globalData.ks;

        // Convert intersection point to world space
        glm::vec4 eyeWorld = intersect.node.transformation * intersect.point; // MAYBE ADD EPSILON

        // Convert surface normal to world space
        glm::mat3x3 threeMat = glm::mat3x3(intersect.node.transformation);
        glm::mat3x3 trans = glm::transpose(glm::inverse(threeMat));

        glm::vec3 surfaceNormal = glm::normalize(trans * glm::vec3(intersect.normal.xyz()));
        glm::vec4 surNorm4 = glm::vec4(surfaceNormal.xyz(), 0.0f);

        // Calculate reflection vector
        glm::vec4 reflectionVec = calculateReflectionVector(surNorm4, -intersect.originalRay); // POTENTIAL ERROR POINT

        // Adding epsilon away in reflection direction to avoid self-intersection
        eyeWorld = eyeWorld + 2.0f*epsilon*reflectionVec;

        CS123ShapeIntersection nextIntersect = findShapeIntersect(eyeWorld, reflectionVec);

        if (nextIntersect.found) {
            glm::vec4 reflectColor = calculateIllumination(nextIntersect, depth + 1);

            sumReflect *= reflectColor;

            return finalVal + sumReflect;
        }
    }

    return finalVal;
}

void RayScene::rayTrace(Canvas2D *canvas, int width, int height, Camera *camera, int r, int c) {
    RGBA *pix = canvas->data();

    int index = r * width + c;

    glm::vec4 pixFilm = screenToFilm((float) c + 0.5, (float) r + 0.5, (float) width, (float) height);

    glm::vec4 pixWorld = filmToWorld(camera, pixFilm);
    glm::vec4 eyeWorld = cameraToWorld(camera, {0, 0, 0, 1});

    glm::vec4 direction = glm::normalize(pixWorld - eyeWorld);

    CS123ShapeIntersection intersect;// = findShapeIntersect(eyeWorld, direction);

    intersect = findShapeIntersect(eyeWorld, direction);

    if (intersect.found) {
        RGBA color = RGBA();
        glm::vec4 illum = calculateIllumination(intersect, 0);
        color.r = illum[0] * 255;
        color.g = illum[1] * 255;
        color.b = illum[2] * 255;
        color.a = 255;
//        std::cout << color.r << ", " << color.g << ", " << color.b << std::endl;
        pix[index] = color;
        canvas->update();
    }
}

void RayScene::rayTraceAA(Canvas2D *canvas, int width, int height, Camera *camera, int r, int c, int numSamples) {
    RGBA *pix = canvas->data();

    int index = r * width + c;

    std::vector<glm::vec4> samplePoints = std::vector<glm::vec4>();

    if (numSamples == 2) {
        glm::vec4 pixFilm1 = screenToFilm((float) c + 0.25, (float) r + 0.25, (float) width, (float) height);
        glm::vec4 pixFilm2 = screenToFilm((float) c + 0.75, (float) r + 0.75, (float) width, (float) height);
        samplePoints.push_back(pixFilm1);
        samplePoints.push_back(pixFilm2);
    } else {
        int sampleJumps = sqrt(numSamples);

        for (int i = 0; i < sampleJumps; i++) {
            for (int j = 0; j < sampleJumps; j++) {
                float jump = 1.0f / sampleJumps;

                glm::vec4 pixFilm = screenToFilm((float) c + ((float)i)*jump, (float) r + ((float)j)*jump, (float) width, (float) height);

                samplePoints.push_back(pixFilm);
            }
        }
    }

    RGBA color = RGBA();
    glm::vec4 illum = glm::vec4(0.0f);

    for (int i = 0; i < (int) samplePoints.size(); i++) {
        glm::vec4 pixFilm = samplePoints.at(i);

        glm::vec4 pixWorld = filmToWorld(camera, pixFilm);
        glm::vec4 eyeWorld = cameraToWorld(camera, {0, 0, 0, 1});

        glm::vec4 direction = glm::normalize(pixWorld - eyeWorld);

        CS123ShapeIntersection intersect;// = findShapeIntersect(eyeWorld, direction);

        intersect = findShapeIntersect(eyeWorld, direction);

        if (intersect.found) {
            illum += calculateIllumination(intersect, 0);
        }
    }
    color.r = (illum[0] * 255) / numSamples;
    color.g = (illum[1] * 255) / numSamples;
    color.b = (illum[2] * 255) / numSamples;
    color.a = 255;
    pix[index] = color;
    canvas->update();
}

//CS123ShapeIntersection RayScene::findShapeIntersectKDTree(glm::vec4 eye, glm::vec4 direction, glm::vec4 pixWorld) {
//    CS123FlatSceneNode bestNode;
//    float tVal = 500; // large value that valid T will be beneath

//    CS123ShapeIntersection intersect = CS123ShapeIntersection();
//    intersect.found = false;

//    KDTreeNode* nearest = m_kdTree.findNearest(pixWorld);

//    CS123ScenePrimitive prim = nearest->sceneNode.primitive;
//    glm::mat4x4 trans = nearest->sceneNode.transformation;

//    // Convert to object space based on stored transfomation
//    glm::vec4 eyeObject = worldToObject(trans, eye);
//    glm::vec4 directionObject = worldToObject(trans, direction);

//    float t;
//    float bodyT;
//    float capT;
//    glm::vec4 normal;

//    switch(prim.type) {
//        case PrimitiveType::PRIMITIVE_CUBE:
//            t = cubeImplicit(eyeObject, directionObject, epsilon);
//            normal = cubeNormal(eyeObject + t*directionObject, epsilon);
//            break;
//        case PrimitiveType::PRIMITIVE_CONE:
//            bodyT = coneBodyImplicit(eyeObject, directionObject);
//            capT = coneCapImplicit(eyeObject, directionObject);
//            if (capT < bodyT) {
//                t = capT;
//                normal = {0, -1, 0, 0};
//            } else {
//                t = bodyT;
//                normal = coneBodyNormal(eyeObject + t*directionObject);
//            }
//            break;
//        case PrimitiveType::PRIMITIVE_CYLINDER:
//            bodyT = cylinderBodyImplicit(eyeObject, directionObject);
//            capT = cylinderCapImplicit(eyeObject, directionObject);
//            if (capT < bodyT) {
//                t = capT;
//                normal = cylinderCapNormal(eyeObject + t*directionObject, epsilon);
//            } else {
//                t = bodyT;
//                normal = cylinderBodyNormal(eyeObject + t*directionObject);
//            }
//            break;
//        case PrimitiveType::PRIMITIVE_SPHERE:
//            t = sphereImplicit(eyeObject, directionObject);
//            normal = glm::normalize(eyeObject + t*directionObject);
//            break;
//        default:
//            std::cerr << "Shape type not found" << std::endl;
//            t = 9999.0f;
//            break;
//    }

//    if (t < tVal) {
//        bestNode = nearest->sceneNode;
//        tVal = t;
//        intersect.found = true;
//        intersect.node = bestNode;
//        intersect.t = tVal;
//        intersect.point = eyeObject + tVal*directionObject; // THIS IS IN OBJECT!!!!
//        intersect.normal = normal;
//        intersect.originalRay = direction;
//    }

//    return intersect;
//}

CS123ShapeIntersection RayScene::findShapeIntersect(glm::vec4 eye, glm::vec4 direction) {

    CS123FlatSceneNode bestNode;
    float tVal = 500; // large value that valid T will be beneath

    CS123ShapeIntersection intersect = CS123ShapeIntersection();
    intersect.found = false;

    for (int i = 0; i < (int) m_flattenedGraph.size(); i++) {

        CS123ScenePrimitive prim = m_flattenedGraph[i].primitive;
        glm::mat4x4 trans = m_flattenedGraph[i].transformation;

        // Convert to object space based on stored transfomation
        glm::vec4 eyeObject = worldToObject(trans, eye);
        glm::vec4 directionObject = worldToObject(trans, direction);

        float t;
        float bodyT;
        float capT;
        glm::vec4 normal;

        switch(prim.type) {
            case PrimitiveType::PRIMITIVE_CUBE:
                t = cubeImplicit(eyeObject, directionObject, epsilon);
                normal = cubeNormal(eyeObject + t*directionObject, epsilon);
                break;
            case PrimitiveType::PRIMITIVE_CONE:
                bodyT = coneBodyImplicit(eyeObject, directionObject);
                capT = coneCapImplicit(eyeObject, directionObject);
                if (capT < bodyT) {
                    t = capT;
                    normal = {0, -1, 0, 0};
                } else {
                    t = bodyT;
                    normal = coneBodyNormal(eyeObject + t*directionObject);
                }
                break;
            case PrimitiveType::PRIMITIVE_CYLINDER:
                bodyT = cylinderBodyImplicit(eyeObject, directionObject);
                capT = cylinderCapImplicit(eyeObject, directionObject);
                if (capT < bodyT) {
                    t = capT;
                    normal = cylinderCapNormal(eyeObject + t*directionObject, epsilon);
                } else {
                    t = bodyT;
                    normal = cylinderBodyNormal(eyeObject + t*directionObject);
                }
                break;
            case PrimitiveType::PRIMITIVE_SPHERE:
                t = sphereImplicit(eyeObject, directionObject);
                normal = glm::normalize(eyeObject + t*directionObject);
                break;
            default:
                std::cerr << "Shape type not found" << std::endl;
                t = 9999.0f;
                break;
        }

        if (t < tVal) {
            bestNode = m_flattenedGraph[i];
            tVal = t;
            intersect.found = true;
            intersect.node = bestNode;
            intersect.t = tVal;
            intersect.point = eyeObject + tVal*directionObject; // THIS IS IN OBJECT!!!!
            intersect.normal = normal;
            intersect.originalRay = direction;
        }
    }

    return intersect;
}

glm::vec2 RayScene::getTextureCoords(CS123ShapeIntersection intersect, int w, int h) {
    int j = intersect.node.primitive.material.textureMap.repeatU;
    int k = intersect.node.primitive.material.textureMap.repeatV;

    glm::vec4 point = intersect.point;

    switch(intersect.node.primitive.type) {
    case PrimitiveType::PRIMITIVE_CONE:
        // bottom face
        if ((point.y >= -0.5f - epsilon) && (point.y <= -0.5f + epsilon)) {
            float u = point.x + 0.5f;
            float v = point.z + 0.5f;

            return calculateTextureCoords(u, v, j, k, w, h);
        } else {
            float u;
            float v = 0.5f - point.y;

            float angle = atan2(point.z, point.x);

            if (angle >= 0) {
                u = 1.0f - (angle/(2*M_PI));
            } else {
                u = -angle / (2*M_PI);
            }
            return calculateTextureCoords(u, v, j, k, w, h);
        }
        break;
    case PrimitiveType::PRIMITIVE_CUBE:
        // left face - assuming negative z goes into screen
        if ((point.x >= -0.5f - epsilon) && (point.x <= -0.5f + epsilon)) {
            float u = point.z + 0.5f;
            float v = 0.5f - point.y;

            return calculateTextureCoords(u, v, j, k, w, h);

        } // right face
        else if ((point.x >= 0.5f - epsilon) && (point.x <= 0.5f + epsilon)) {
            float u = 0.5f - point.z;
            float v = 0.5f - point.y;

            return calculateTextureCoords(u, v, j, k, w, h);
        } // bottom face
        else if ((point.y >= -0.5f - epsilon) && (point.y <= -0.5f + epsilon)) {
            float u = point.x + 0.5f;
            float v = 0.5f - point.z;

            return calculateTextureCoords(u, v, j, k, w, h);
        } // top face
        else if ((point.y >= 0.5f - epsilon) && (point.y <= 0.5f + epsilon)) {
            float u = point.x + 0.5f;
            float v = point.z + 0.5f;

            return calculateTextureCoords(u, v, j, k, w, h);
        } // back face
        else if ((point.z >= -0.5f - epsilon) && (point.z <= -0.5f + epsilon)) {
            float u = 0.5f - point.x;
            float v = 0.5f - point.y;

            return calculateTextureCoords(u, v, j, k, w, h);
        } // front face
        else if ((point.z >= 0.5f - epsilon) && (point.z <= 0.5f + epsilon)) {
             float u = point.x + 0.5f;
             float v = 0.5f - point.y;

             return calculateTextureCoords(u, v, j, k, w, h);
        }
        break;
    case PrimitiveType::PRIMITIVE_SPHERE:
        // just added this if-statement cause there was an error with "jumping to next case"
        if (true) {
            float u;
            float v;

            float angle = atan2(point.z, point.x);

            if (angle >= 0) {
                u = 1.0f - (angle/(2*M_PI));
            } else {
                u = -angle / (2*M_PI);
            }

            float latitude = asin(point.y/0.5f);
            v = (latitude/M_PI) + 0.5f;

            return calculateTextureCoords(u, v, j, k, w, h);
        }
        break;
    case PrimitiveType::PRIMITIVE_CYLINDER:
        // bottom face
        if ((point.y >= -0.5f - epsilon) && (point.y <= -0.5f + epsilon)) {
            float u = point.x + 0.5f;
            float v = 0.5f - point.z;

            return calculateTextureCoords(u, v, j, k, w, h);
        } // top face
        else if ((point.y >= 0.5f - epsilon) && (point.y <= 0.5f + epsilon)) {
            float u = point.x + 0.5f;
            float v = point.z + 0.5f;

            return calculateTextureCoords(u, v, j, k, w, h);
        } else {
            float u;
            float v = 0.5f - point.y;

            float angle = atan2(point.z, point.x);

            if (angle >= 0) {
                u = 1.0f - (angle/(2*M_PI));
            } else {
                u = -angle / (2*M_PI);
            }
            return calculateTextureCoords(u, v, j, k, w, h);
        }
        break;
    default:
        break;
    }
    return glm::vec2();
}

/* u and v are the x and y values in the unit square that a particular point on an object
   gets mapped to. j and k are the number of repetitions in the x and
   y directions, respectively. w is the texture width, and h is the texture height. */
glm::vec2 RayScene::calculateTextureCoords(float u, float v, int j, int k, int w, int h) {
    glm::vec2 st;
    st[0] = ((int)(u * j * w)) % w;
    st[1] = ((int)(v * k * h)) % h;
    return st;
}

glm::vec4 RayScene::calculateReflectionVector(glm::vec4 normal, glm::vec4 pointToLight) {
    glm::vec4 reflect = 2.0f * normal * glm::clamp(glm::dot(normal, pointToLight), 0.0f, 1.0f) - pointToLight;
    return glm::normalize(reflect);
}

glm::vec4 RayScene::cubeNormal(glm::vec4 point, float epsilon) {
    if (abs(point[0] - 0.5) < epsilon) {
        return {1, 0, 0, 0};
    } else if (abs(point[0] + 0.5) < epsilon) {
        return {-1, 0, 0, 0};
    } else if (abs(point[1] - 0.5) < epsilon) {
        return {0, 1, 0, 0};
    } else if (abs(point[1] + 0.5) < epsilon) {
        return {0, -1, 0, 0};
    } else if (abs(point[2] - 0.5) < epsilon) {
        return {0, 0, 1, 0};
    } else if (abs(point[2] + 0.5) < epsilon) {
        return {0, 0, -1, 0};
    }
    return {0, 0, 0, 0};
}

glm::vec4 RayScene::cylinderCapNormal(glm::vec4 point, float epsilon) {
    if (abs(point[1] - 0.5) < epsilon) {
        return {0, 1, 0, 0};
    } else if (abs(point[1] + 0.5) < epsilon) {
        return {0, -1, 0, 0};
    }
}

glm::vec4 RayScene::cylinderBodyNormal(glm::vec4 point) {
    glm::vec4 norm = {point[0], 0, point[2], 0};
    return glm::normalize(norm);
}

glm::vec4 RayScene::coneBodyNormal(glm::vec4 point) {
    glm::vec4 normal = glm::vec4();

    normal[0] = point[1]/0.5f * (2/sqrt(5));
    normal[1] = 1 / sqrt(5);
    normal[2] = point[2]/0.5f * (2/sqrt(5));
    normal[3] = 0;

    return glm::normalize(normal);
}

float RayScene::coneBodyImplicit(glm::vec4 eye, glm::vec4 dir) {
    //possibly do a check at the beginning for bounds?
    float A = (pow(dir[0], 2) + pow(dir[2], 2) - .25f * pow(dir[1], 2));
    float B = (2.0f *eye[0]*dir[0] + 2.0f*eye[2]*dir[2] -.5f*eye[1]*dir[1] + .25f*dir[1]);
    float C = (pow(eye[0], 2) + pow(eye[2], 2) - .25f*pow(eye[1], 2) + .25f*eye[1] - (1.0f/16.0f));

    float discrim = pow(B, 2) - 4*A*C;

    if (discrim >= 0.0f) {
        float plusT = (-B + sqrt(discrim)) / (2*A);
        float minusT = (-B - sqrt(discrim)) / (2*A);

        // CHECKING BOUNDS!!!
        float y1 = eye[1] + dir[1]*plusT;
        float y2 = eye[1] + dir[1]*minusT;

        // If both are valid intersections
        if ((-0.5 <= y1 && y1 <= 0.5) && (-0.5 <= y2 && y2 <= 0.5)) {

            if (plusT >= 0 && minusT >= 0) {
                return std::min(plusT, minusT);
            } else if (plusT >= 0) {
                return plusT;
            } else if (minusT >= 0) {
                return minusT;
            } else {
                return 9999.0f;
            }

        } else if (-0.5 <= y1 && y1 <= 0.5) {

            if (plusT >= 0) {
                return plusT;
            } else {
                return 9999.0f;
            }
        } else if (-0.5 <= y2 && y2 <= 0.5) {

            if (minusT >= 0) {
                return minusT;
            } else {
                return 9999.0f;
            }
        } else {
            return 9999.0f; // return large val??
        }

    } else {
        return 9999.0f; // return large val?
    }
}

float RayScene::coneCapImplicit(glm::vec4 eye, glm::vec4 dir) {
    glm::vec4 normal = {0.0f, -1.0f, 0.0f, 0};

    float t = (-.5 - eye[1]) / dir[1];

    float x = eye[0] + dir[0]*t;
    float z = eye[2] + dir[2]*t;

    // CHECKING BOUNDS
    if (pow(x, 2) + pow(z, 2) <= pow(0.5, 2)) {
        if (t >= 0) {
            return t;
        } else {
            return 9999.0f;
        }
    } else {
        return 9999.0f;
    }
}

float RayScene::cylinderBodyImplicit(glm::vec4 eye, glm::vec4 dir) {
    //possibly do a check at the beginning for bounds?
    float A = (pow(dir[0], 2) + pow(dir[2], 2));
    float B = (2.0f *eye[0]*dir[0] + 2.0f*eye[2]*dir[2]);
    float C = (pow(eye[0], 2) + pow(eye[2], 2) - pow(.5, 2));

    float discrim = pow(B, 2) - 4*A*C;

    if (discrim >= 0.0f) {
        float plusT = (-B + sqrt(discrim)) / (2.0f*A);
        float minusT = (-B - sqrt(discrim)) / (2.0f*A);

        // CHECKING BOUNDS!!!
        float y1 = eye[1] + dir[1]*plusT;
        float y2 = eye[1] + dir[1]*minusT;

        // If both are valid intersections
        if ((-0.5 <= y1 && y1 <= 0.5) && (-0.5 <= y2 && y2 <= 0.5)) {
            if (plusT >= 0.0f && minusT >= 0.0f) {
                return std::min(plusT, minusT);
            } else if (plusT >= 0.0f) {
                return plusT;
            } else if (minusT >= 0.0f) {
                return minusT;
            } else {
                return 9999.0f;
            }

        } else if (-0.5 <= y1 && y1 <= 0.5) {
            if (plusT >= 0.0f) {
                return plusT;
            } else {
                return 9999.0f;
            }
        } else if (-0.5 <= y2 && y2 <= 0.5) {
            if (minusT >= 0.0f) {
                return minusT;
            } else {
                return 9999.0f;
            }
        } else {
            return 9999.0f; // return large val??
        }

    } else {
        return 9999.0f; // return large val?
    }
}

float RayScene::cylinderCapImplicit(glm::vec4 eye, glm::vec4 dir) {
    glm::vec4 topNormal = {0.0f, 1.0f, 0.0f, 0};
    glm::vec4 botNormal = {0.0f, -1.0f, 0.0f, 0};
    float y1 = -0.5f;
    float y2 = 0.5f;

    float t1 = (y1 - eye[1]) / dir[1];
    float t2 = (y2 - eye[1]) / dir[1];

    float x1 = eye[0] + dir[0]*t1;
    float z1 = eye[2] + dir[2]*t1;

    float x2 = eye[0] + dir[0]*t2;
    float z2 = eye[2] + dir[2]*t2;


    // CHECKING BOUNDS
    bool t1Valid = pow(x1, 2) + pow(z1, 2) <= pow(0.5, 2);
    bool t2Valid = pow(x2, 2) + pow(z2, 2) <= pow(0.5, 2);

    if (t1Valid && t2Valid) {
        if (t1 >= 0 && t2 >= 00) {
            return std::min(t1, t2);
        } else if (t1 >= 0) {
            return t1;
        } else if (t2 >= 0) {
            return t2;
        } else {
            return 9999.0f;
        }

    } else if (t1Valid) {
        if (t1 >= 0) {
            return t1;
        } else {
            return 9999.0f;
        }
    } else if (t2Valid) {
        if (t2 >= 0) {
            return t2;
        } else {
            return 9999.0f;
        }
    } else {
        return 9999.0f;
    }
}

float RayScene::sphereImplicit(glm::vec4 eye, glm::vec4 dir) {
    float A = pow(dir[0], 2) + pow(dir[1], 2) + pow(dir[2], 2);
    float B = 2.0f*dir[0]*eye[0] + 2.0f*dir[1]*eye[1] + 2.0f*dir[2]*eye[2];
    float C = pow(eye[0], 2) + pow(eye[1], 2) + pow(eye[2], 2) - pow(0.5f, 2);

    float discrim = pow(B, 2) - 4*A*C;

    if (discrim >= 0.0f) {
        float t1 = (-B + sqrt(discrim))/(2*A);
        float t2 = (-B - sqrt(discrim))/(2*A);

        if (t1 >= 0.0f && t2 >= 0.0f) {
            return std::min(t1, t2);
        } else if (t1 >= 0.0f) {
            return t1;
        } else if (t2 >= 0.0f) {
            return t2;
        } else {
            return 9999.0f;
        }

    } else {
        return 9999.0f;
    }
}

float RayScene::cubeImplicit(glm::vec4 eye, glm::vec4 dir, float epsilon) {
    float t = 9999.9f;
    std::vector<float> tVals = std::vector<float>();
    tVals.push_back((-.5 - eye[0]) / dir[0]);
    tVals.push_back((.5 - eye[0]) / dir[0]);
    tVals.push_back((-.5 - eye[1]) / dir[1]);
    tVals.push_back((.5 - eye[1]) / dir[1]);
    tVals.push_back((-.5 - eye[2]) / dir[2]);
    tVals.push_back((.5 - eye[2]) / dir[2]);

    for (int i = 0; i < (int) tVals.size(); i++) {
        float x = eye[0] + tVals[i]*dir[0];
        float y = eye[1] + tVals[i]*dir[1];
        float z = eye[2] + tVals[i]*dir[2];

        bool xValid = -0.5 - epsilon <= x && x <= 0.5 + epsilon;
        bool yValid = -0.5 - epsilon <= y && y <= 0.5 + epsilon;
        bool zValid = -0.5 - epsilon <= z && z <= 0.5 + epsilon;

        if (xValid && yValid && zValid) {
            if (tVals[i] >= 0) {
                if (tVals[i] < t) {
                    t = tVals[i];
                }
            }
        }
    }
    return t;
}

glm::vec4 RayScene::worldToObject(glm::mat4x4 transformation, glm::vec4 point) {
    return glm::inverse(transformation) * point; // switched??
}

glm::vec4 RayScene::screenToFilm(float x, float y, float width, float height) {
    float px = (2*x/width) - 1;
    float py = 1 - (2*y/height);
    float pz = -1;

    return glm::vec4(px, py, pz, 1);
}

glm::vec4 RayScene::filmToWorld(Camera *camera, glm::vec4 point) {
//    return camera->getInverseViewMatrix() * glm::inverse(camera->getScaleMatrix()) * point; // hmmmmmmmmmmm
    return glm::inverse(camera->getViewMatrix()) * glm::inverse(camera->getScaleMatrix()) * point; // hmmmmmmmmmmm
}

glm::vec4 RayScene::cameraToWorld(Camera *camera, glm::vec4 point) {
    return glm::inverse(camera->getViewMatrix()) * point;
}
