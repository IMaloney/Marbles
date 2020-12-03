/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>

CamtransCamera::CamtransCamera() :
    m_aspectRatio(1.0),
    m_near(1.0),
    m_far(30.0),
    m_thetaH(60.f)
{
    // changed look vector from 0,0,0 to 2,2,2 (emulate camera eye)
    this->setHeightAngle(m_thetaH);
     this->orientLook(glm::vec4(2.f,2.f,2.f, 1.f), glm::vec4(-2.f, -2.f, -2.f, 0.f), glm::vec4(0.f, 1.f, 0.f, 0.f));

}

void CamtransCamera::setAspectRatio(float a)
{
    m_aspectRatio = a;
    this->setHeightAngle(m_thetaH);
    this->updateProjectionMatrix();
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    return m_perspectiveTransformation * m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    return m_rotationMatrix * m_translationMatrix;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    return m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    return m_perspectiveTransformation;
}

glm::vec4 CamtransCamera::getPosition() const {
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const {
    return -m_w;
}

glm::vec4 CamtransCamera::getUp() const {
    return m_up;
}

float CamtransCamera::getAspectRatio() const {
    return m_aspectRatio;
}

float CamtransCamera::getHeightAngle() const {
    return m_thetaH;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    m_eye = eye;
    m_up = glm::normalize(up);
    m_w = glm::normalize(-look);
    m_v = glm::normalize(up - glm::dot(up, m_w) * m_w);
    m_u = glm::normalize(glm::vec4(glm::cross(m_v.xyz(), m_w.xyz()), 0.f));
    this->updateViewMatrix();
    this->upatePerspectiveMatrix();
}

void CamtransCamera::setHeightAngle(float h) {
    m_thetaH = h;
    m_thetaW = glm::degrees(2.f * glm::atan(glm::tan(glm::radians(m_thetaH/2.f)) * m_aspectRatio)); // glm::tan(glm::radians(m_thetaH/2.f)) * m_aspectRatio
    this->updateProjectionMatrix();

}

void CamtransCamera::translate(const glm::vec4 &v) {
    m_eye += v;
    this->updateViewMatrix();
}

void CamtransCamera::rotateU(float degrees) {
    float r = glm::radians(degrees);
    glm::vec4 tempV = m_v;
    m_v = (m_w * std::sin(r)) + (m_v * std::cos(r));
    m_w = (m_w  * std::cos(r)) - (tempV * std::sin(r));
    this->updateViewMatrix();
}

void CamtransCamera::rotateV(float degrees) {
    float r = glm::radians(degrees);
    glm::vec4 tempU = m_u;
    m_u = (m_u * std::cos(r)) - (m_w * std::sin(r));
    m_w = (tempU * std::sin(r)) + (m_w *std::cos(r));
    this->updateViewMatrix();
}

void CamtransCamera::rotateW(float degrees) {
    float r = glm::radians(-degrees);
    glm::vec4 tempW = m_u;
    m_u = (m_u * std::cos(r)) - (m_v * std::sin(r));
    m_v = (tempW * std::sin(r)) + (m_v * std::cos(r));
    this->updateViewMatrix();

}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    m_near = nearPlane;
    m_far = farPlane;
    this->updateProjectionMatrix();
}


glm::vec4 CamtransCamera::getU() const {
    return m_u;
}

glm::vec4 CamtransCamera::getV() const {
    return m_v;
}

glm::vec4 CamtransCamera::getW() const {
    return m_w;
}

void CamtransCamera::updateProjectionMatrix(){
    this->updateScaleMatrix();
    this->upatePerspectiveMatrix();
}

void CamtransCamera::upatePerspectiveMatrix(){
    float c = -1.f * (m_near/m_far);
    float p1 = -1.f/(c + 1.f);
    float p2 = c/(c+1);
    m_perspectiveTransformation = glm::transpose(glm::mat4(1.f,      0.f,      0.f,      0.f,
                                                           0.f,      1.f,      0.f,      0.f,
                                                           0.f,      0.f,      p1,       p2,
                                                           0.f,      0.f,      -1.f,     0.f));
}

void CamtransCamera::updateScaleMatrix(){
    float x = (1.f/(m_far * std::tan(glm::radians(m_thetaW/2.f)))),
          y = 1.f/(m_far * std::tan(glm::radians(m_thetaH/2.f))),
          z = 1.f/m_far;
    m_scaleMatrix = glm::transpose(glm::mat4(x,      0.f,      0.f,      0.f,
                                             0.f,    y,        0.f,      0.f,
                                             0.f,    0.f,      z,        0.f,
                                             0.f,    0.f,      0.f,      1.f));
}

void CamtransCamera::updateViewMatrix(){
    this->updateTranslationMatrix();
    this->updateRotationMatrix();
}

void CamtransCamera::updateRotationMatrix(){
    m_rotationMatrix = glm::transpose(glm::mat4(m_u.x,       m_u.y,      m_u.z,      0.f,
                                                m_v.x,       m_v.y,      m_v.z,      0.f,
                                                m_w.x,       m_w.y,      m_w.z,      0.f,
                                                0.f,         0.f,        0.f,        1.f));
}

void CamtransCamera::updateTranslationMatrix(){
    glm::vec3 pn = -1.f * m_eye.xyz();
    m_translationMatrix = glm::transpose(glm::mat4(1.f, 0.f, 0.f, pn.x,
                                                   0.f, 1.f, 0.f, pn.y,
                                                   0.f, 0.f, 1.f, pn.z,
                                                   0.f, 0.f, 0.f, 1.f));
}

